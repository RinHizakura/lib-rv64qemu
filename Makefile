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
LIBRV64QEMU = librv64qemu.a
EXAMPLE = $(OUT)/hello

GIT_HOOKS := .git/hooks/applied
LIB_OBJ = $(OUT)/crt.o $(OUT)/init.o $(OUT)/setup.o $(OUT)/device.o $(OUT)/uart16550.o

all: $(GIT_HOOKS) $(LIBRV64QEMU) $(EXAMPLE)

$(GIT_HOOKS):
	@scripts/install-git-hooks
	@echo

$(LIBRV64QEMU): $(LIB_OBJ)
	$(AR) cr $@ $(LIB_OBJ)

$(OUT)/%.o: lib/arch/$(ARCH)/%.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/%.o: lib/drivers/%.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/%.o: lib/arch/$(ARCH)/machine/$(MACHINE)/%.s
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/%.o: lib/arch/$(ARCH)/machine/$(MACHINE)/%.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(OUT)/%.o: example/%.c
	mkdir -p $(@D)
	$(CC) -c $(CFLAGS) $< -o $@

$(EXAMPLE): %: %.o $(LIBRV64QEMU)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

qemu: $(LIBRV64QEMU) $(EXAMPLE)
	qemu-system-riscv64 -nographic -machine virt \
		-serial mon:stdio \
		-cpu rv64 -bios none -kernel $(EXAMPLE)
clean:
	$(RM) -rf build
	$(RM) -rf $(LIBRV64QEMU)
