ENTRY(tboot_main)
OUTPUT_FORMAT("elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)

SECTIONS
{
    /* ========== Per Cpu variables ========== */
    . = 0x0;
    .pcpu_data (NOLOAD) : {
        *(.pcpu_data*)
    }
    kernel_pcpu_data_size = .;

    /* ========== TomatBoot stub ========== */
	. = 0x0100000;
	kernel_physical_start = .;

    .tboot.text ALIGN(4K) :
    {
	    *(.tboot.text)
    }

    /* ========= Kernel code ========= */
    . += 0xFFFFFFFFC0000000;
	.text ALIGN(4K) : AT (ADDR (.text) - 0xFFFFFFFFC0000000)
	{
	    *(.text*)
	}

    .rodata ALIGN(4K) : AT (ADDR (.rodata) - 0xFFFFFFFFC0000000)
    {
        *(.rodata*)
    }

	.data ALIGN(4K) : AT (ADDR (.data) - 0xFFFFFFFFC0000000)
	{
	    *(.data*)

	    bsp_pcpu_data = .;
	    FILL(0x00)
	    . += ABSOLUTE(kernel_pcpu_data_size);
	}

	.bss ALIGN(4K) : AT (ADDR (.bss) - 0xFFFFFFFFC0000000)
	{
	    *(COMMON)
	    *(.bss*)
	}

	kernel_physical_end = . - 0xFFFFFFFFC0000000;
	kernel_virtual_end = .;
}