ENTRY(_start)

MEMORY {
	ram : ORIGIN = 0x8000,  LENGTH = 0x40000000
}

SECTIONS {
	. = 0x8000;
	.init : { *(.init) } > ram
	.text : { *(.text) } > ram
	.data : { *(.data) } > ram
	.bss  : { *(.bss)  } > ram
}
