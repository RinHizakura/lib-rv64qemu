/* To know more about this linker script, I would suggest you to read this:
 * - https://github.com/sgmarz/osblog/blob/master/risc_v/src/lds/virt.lds */

OUTPUT_ARCH(riscv)

ENTRY(_start)

MEMORY
{
  ram  (wxa!ri) : ORIGIN = 0x80000000, LENGTH = 128M
}

PHDRS
{
  text PT_LOAD;
  data PT_LOAD;
  bss PT_LOAD;
}

SECTIONS
{
    .text : { 
        *(.text.boot)
        *(.text .text.*)
    }  >ram AT>ram :text 

    .rodata : {
        *(.rodata .rodata.*)
    }  >ram AT>ram :text

    . = ALIGN(4K);
    .data : { 
        *(.sdata .sdata.*) *(.data .data.*)
    }  >ram AT>ram :data

    . = ALIGN(4K);
    .bss : { 
          _bss_start = .;
         *(.sbss .sbss.*) *(.bss .bss.*)
         _bss_end = .;
    }  >ram AT>ram :bss

    . = ALIGN(4K);
    /* 64KB is reserved for stack */
    _stack_start = .;
    _stack_end = _stack_start + 0x10000;
}
