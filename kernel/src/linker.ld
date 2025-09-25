ENTRY(_start)

SECTIONS
{
  . = 1M;   /* Kernel wird bei 1 MB geladen */

  .text : {
    *(.multiboot)   /* Multiboot Header zuerst! */
    *(.text*)
  }

  .rodata : { *(.rodata*) }
  .data :   { *(.data*) }
  .bss :    { *(.bss*) }
}
