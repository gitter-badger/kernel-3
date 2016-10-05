#include <stdint.h>
#include <print.h>
#include <vm.h>

#include <bcm_2836.h>
#include <mmap.h>

extern char __kern_virt_base;


void kmain()
{
	print_init();
	vaddr_t kernel_base = (vaddr_t) &__kern_virt_base;
	kprintf("Hello racoon at 0x%x! Booting...\n", kernel_base);

	// init memory map

	// set up proper page table

	// install exceptions

	// start first user process
}

