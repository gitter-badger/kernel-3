#include <stdint.h>
#include <vm.h>

extern char __kern_phys_base;
extern char __kern_virt_base;
extern char __kern_size;
static paddr_t kernel_start = (paddr_t) &__kern_phys_base;
static paddr_t kernel_size = (paddr_t) &__kern_size;

extern void set_pd_bootstrap(pde_t *pde);
extern void enable_mmu();

// bss segments
extern char __bootstrap_end_data;
extern char __bootstrap_end;

extern char __unpaged_end_data;
extern char __unpaged_end;

// Reserve space for a page directory
pde_t __attribute__((aligned(4096))) page_directory[VM_PD_SIZE];
pte_t __attribute__((aligned(4096))) kernel_pt[VM_PT_SIZE];


static void *memset_unpaged(void *ptr, uint8_t value, uint32_t num)
{
	uint8_t * p = ptr;
	for (uint32_t i = 0; i < num; ++i)
	{
		*p = value;
		++p;
	}

	return ptr;
}

static void setup_one_to_one_mappings(pde_t *pd)
{

	pd[0] = 0x0 | (0x1 << 7) | (0x1 << 1) | 0x1; // present and 4Mb

	// map last entry to itself
	pd[VM_PD_SIZE-1] = (unsigned long)pd | 0x1;
}

static vaddr_t map_kernel(pde_t *pd)
{
	const vaddr_t kernel_virt = (vaddr_t) &__kern_virt_base;
	paddr_t kernel_phys = kernel_start;

	// find out which directory entry the
	// kernel should go into
	uint32_t pde_index = kernel_virt / (4096*1024);

	// map directories
	pd[pde_index] = (paddr_t) kernel_pt | 0x1;

	// todo: this assumes that kernel_size < 4Mb
	uint32_t mapped = 0;
	uint32_t index = 0;
	while (mapped < kernel_size && index < VM_PT_SIZE) {

		kernel_pt[index] = kernel_phys | 0x1;

		++index;
		mapped += 4096; // 4 Kb
		kernel_phys += 4096; // 4kb
	}

	return kernel_virt;
}

void pre_init()
{
	// clear bss (both temp bootstrap one
	// and future kernel one).
	// Need to use physical addresses (unpaged)
	// here since the MMU is not set up yet
	memset_unpaged(&__unpaged_end_data, 0,
			(uint32_t)&__unpaged_end -
			(uint32_t)&__unpaged_end_data);

	memset_unpaged(page_directory, 0, sizeof(pde_t) * VM_PD_SIZE);

	// this code needs to stay where it is
	setup_one_to_one_mappings(page_directory);

	// map the kernel high where it
	// expects to be
	map_kernel(page_directory);

	// set the newly initialized page directory
	set_pd_bootstrap(page_directory);

	// enable the mmu
	enable_mmu();
}
