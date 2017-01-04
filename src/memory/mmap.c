#include <mmap.h>

void mm_init(struct memmap *mm, uint32_t page_size)
{
	mm->page_size = page_size;
	mm->dev_mappings.num_mappings = 0;
}

void mm_add_device_mapping(struct memmap *mm,
		paddr_t start,
		uint32_t size)
{
	struct device_mappings *dm = &mm->dev_mappings;

	// add to map
	const uint32_t num_pages = size / mm->page_size;
	struct device_mapping *m = &dm->mappings[dm->num_mappings];
	m->start = start;
	m->num_pages = num_pages;

	++dm->num_mappings;
}

struct device_mappings *mm_get_device_mappings(struct memmap *mm)
{
	return &mm->dev_mappings;
}
