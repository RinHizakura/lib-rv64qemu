ARCH =  riscv
MACHINE = qemu-virt

CC = riscv64-unknown-elf-gcc
AR = riscv64-unknown-elf-ar
LINKER_SRC = linker_scripts/machine/$(MACHINE)/linker.ld
CFLAGS = -march=rv64imac -mabi=lp64 -mcmodel=medany -ffunction-sections -fdata-sections
CFLAGS += -Iinclude
LDFLAGS = -nostdlib -nostartfiles -static \
          -Wl,--gc-sections -T$(LINKER_SRC)

CURDIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
OUT ?= build
SHELL_HACK := $(shell mkdir -p $(OUT))

GIT_HOOKS := .git/hooks/applied

LIBRV64QEMU = librv64qemu.a
LIB_CSRCS = $(shell find ./lib -name '*.c')
_LIB_OBJ =  $(notdir $(LIB_CSRCS))
LIB_OBJ = $(_LIB_OBJ:%.c=$(OUT)/%.o)
LIB_OBJ += $(OUT)/crt.o

EXAMPLE = $(OUT)/hello
EXAMPLE_CSRCS = $(shell find ./example -name '*.c')
EXAMPLE_OBJ = $(OUT)/hello.o

vpath %.c $(sort $(dir $(LIB_CSRCS)))
vpath %.c $(sort $(dir $(EXAMPLE_CSRCS)))

all: $(GIT_HOOKS) $(LIBRV64QEMU) $(EXAMPLE)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

$(LIBRV64QEMU): $(LIB_OBJ)
	$(AR) cr $@ $(LIB_OBJ)

$(OUT)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/%.o: lib/arch/$(ARCH)/machine/$(MACHINE)/%.s
	$(CC) -c $(CFLAGS) $< -o $@

$(EXAMPLE): %: %.o $(LIBRV64QEMU)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

qemu: $(LIBRV64QEMU) $(EXAMPLE)
	qemu-system-riscv64 -nographic -machine virt \
		-serial mon:stdio \
		-cpu rv64 -bios none -kernel $(EXAMPLE)
clean:
	$(RM) $(LIB_OBJ) $(EXAMPLE_OBJ)
	$(RM) $(LIBRV64QEMU) $(EXAMPLE)
