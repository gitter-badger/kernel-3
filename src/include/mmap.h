#pragma once

// TODO: this is needed for types, they should maybe
// be in another header
#include <vm.h>
#include <stdint.h>

#define MAX_DEVICE_MAPPINGS 64

struct device_mapping
{
	paddr_t start;
	uint32_t num_pages;
};

struct device_mappings
{
	uint32_t num_mappings;
	struct device_mapping mappings[MAX_DEVICE_MAPPINGS];
};

struct memmap
{
	uint32_t page_size;
	struct device_mappings dev_mappings;
};

void mm_init(struct memmap *mm, uint32_t page_size);

void mm_add_device_mapping(struct memmap *mm,
		paddr_t start,
		uint32_t size);

struct device_mappings *mm_get_device_mappings(struct memmap *mm);

paddr_t mm_alloc_physical_pages(struct memmap *mm,
		paddr_t start,
		uint32_t size);
