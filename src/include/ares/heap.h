
/*
 * Ares 64-bit Operating System
 *
 * Heap allocation memory manager
 */

#ifndef __ares_heap_h_

#define __ares_heap_h_

#include <types.h>

typedef struct {
    uint8_t is_free;
    uint32_t size;
} heap_metadata_t;

typedef struct heap_block {
    heap_metadata_t metadata;
    void* data;
    struct heap_block* next;
} heap_block_t;

int32_t kheap_init(void* start, void* end);
void* kmalloc(uint32_t size);
void* kcalloc(uint32_t n, uint32_t size);
void* krealloc(void* ptr, uint32_t size);
void  kfree(void* ptr);

#endif /* __ares_heap_h_ */