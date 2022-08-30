HEAP_SIZE  = DEFINED(__heap_size__)  ? __heap_size__  : 0x00000050;
STACK_SIZE = DEFINED(__stack_size__) ? __stack_size__ : 0x00000400;

MEMORY
{
  FLASH               (RX)  : ORIGIN = 0x00000000, LENGTH = 0x10000
  SRAM                (RW)  : ORIGIN = 0x20000000, LENGTH = 0x10000
}

SECTIONS
{
  /* The startup code goes first into internal flash */
  .interrupts :
  {
    FILL(0x01020304);
    __VECTOR_TABLE = .;
    . = ALIGN(4);
    KEEP(*(.isr_vector))     /* Startup code */
    . = ALIGN(4);
  } > FLASH

  /* The program code and other data goes into internal flash */
  .text :
  {
    FILL(0x01020304);
    . = ALIGN(4);
    *(.text)                 /* .text sections (code) */
    *(.text*)                /* .text* sections (code) */
    *(.rodata)               /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)              /* .rodata* sections (constants, strings, etc.) */
    *(.glue_7)               /* glue arm to thumb code */
    *(.glue_7t)              /* glue thumb to arm code */
    *(.eh_frame)
    KEEP (*(.init))
    KEEP (*(.fini))
    FILL(0x00000000);
    . = ALIGN(4);
    FILL(0x01020304);
    . = ALIGN(16);
  } > FLASH

  /* Uninitialized data section */
  .bss :
  {
    /* This is used by the startup in order to initialize the .bss section */
    . = ALIGN(4);
    __START_BSS = .;
    __bss_start__ = .;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    __bss_end__ = .;
    __END_BSS = .;
  } > SRAM

  .heap :
  {
    . = ALIGN(8);
    __end__ = .;
    _end = .;
    PROVIDE(end = .);
    __HeapBase = .;
    . += HEAP_SIZE;
    __HeapLimit = .;
  } > SRAM

  .stack :
  {
    . = ALIGN(8);
    . += STACK_SIZE;
  } > SRAM

  __StackTop   = .;
  _vStackTop   = .;
  __StackLimit = __StackTop - STACK_SIZE;
  PROVIDE(__stack = __StackTop);
}
