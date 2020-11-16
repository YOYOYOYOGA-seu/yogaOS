ENTRY(_start)
SECTIONS
{
    . = 0x40001000; 
    .text :
    {
        */start.o(.text)
         *(.text)
    }
    .data : { *(.data) }
    . = 0x40070000;
    .bss : { *(.bss) }
}