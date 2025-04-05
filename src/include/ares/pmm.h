/**
* Ares 64-bit operating system
 *
 * Virtual memory mapping
 */

#ifndef __ares_pmm_h_
#define __ares_pmm_h_

#include <ares/types.h>

void pmm_init(uint32_t memory_base, uint32_t memory_size);
void pmm_init_from_mb2();

void* pmm_alloc();
void pmm_free(void* addr);

size_t pmm_get_used();
size_t pmm_get_total();

#endif //__ares_pmm_h_
