#include <stdint.h>
#include <vm.h>

extern char __kern_phys_base;
extern char __kern_virt_base;
extern char __kern_size;
static paddr_t kernel_start = (paddr_t) &__kern_phys_base;
static paddr_t kernel_size = (paddr_t) &__kern_size;

extern void set_pd(pde_t *pde);
extern void enable_mmu();

// bss segments
extern char __bootstrap_end_data;
extern char __bootstrap_end;

extern char __unpaged_end_data;
extern char __unpaged_end;

// Reserve space for a page directory
pde_t __attribute__((aligned(4096))) page_directory[VM_PDE_SIZE];

// Reserve space for two page tables, one for identity mapping first Mb
// and one for recursive pde mapping
pte_t __attribute__((aligned(4096))) pt_recursive[VM_PDE_SIZE];


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
	pd[0] = 0x0 | (0x1 << 8) | 0x1; // present and 4Mb
}

static vaddr_t map_kernel(pde_t *pd)
{
	const vaddr_t kernel_virt = (vaddr_t) &__kern_virt_base;
	paddr_t kernel_phys = kernel_start;

	// find out which directory entry the
	// kernel should go into
	pde_t pde = kernel_virt / (4096*1024);

	// map directories
	uint32_t mapped = 0;
	while (mapped < kernel_size) {

		pd[pde] = kernel_phys
			| (0x1 << 8)
			| 0x1;


		mapped += 4096*1024;
		kernel_phys += 4096*1024;
		++pde;
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

	memset_unpaged(&__bootstrap_end_data, 0,
			(uint32_t)&__bootstrap_end -
			(uint32_t)&__bootstrap_end_data);

	// this code needs to stay where it is
	setup_one_to_one_mappings(page_directory);

	// map the kernel high where it
	// expects to be
	map_kernel(page_directory);

	// set the newly initialized page directory
	set_pd(page_directory);

	// enable the mmu
	enable_mmu();
}
