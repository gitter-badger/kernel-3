#pragma once

typedef unsigned long vaddr_t;
typedef unsigned long paddr_t;
typedef unsigned long pde_t;
typedef unsigned long pte_t;

#define VM_PDE_SIZE 1024
#define VM_PTE_SIZE 1024

/*!
 * Bootstrap method for kernel
 */
/*struct pagetable *vm_init(struct memmap *mm,
		paddr_t kernel_phys,
		uint32_t kernel_size,
		vaddr_t kernel_virt);

struct pagetable *vm_creatept(struct memmap *mm,
		paddr_t kernel_phys,
		uint32_t kernel_size,
		vaddr_t kernel_virt);

int vm_setactivept(struct pagetable *pt);

int vm_alloc(struct pagetable *pt, vaddr_t start, uint32_t num_pages);
int vm_free(struct pagetable *pt, vaddr_t start);*/
