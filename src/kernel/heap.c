
#include <heap.h>
#include <kernel.h>
#include <string.h>

void *kheap_start_addr = NULL, *kheap_end_addr = NULL;

uint64_t total_size = 0;
uint64_t total_used_size = 0;
heap_block_t *head = NULL;

int32_t kheap_init(void *start_addr, void *end_addr) {
    if (start_addr >= end_addr) {
        PANIC("Unable to init kernel heap");
        return -1;
    }

    kheap_start_addr = start_addr;
    kheap_end_addr = end_addr;

    total_size = (uint64_t)(end_addr - start_addr);
    total_used_size = 0;

    head = NULL;

    return 0;
}

/**
 * Increases heap memory by requested size and returns its address.
 */
void *kbrk(uint32_t size) {
    if (total_used_size + size > total_size) {
        return NULL;
    }

    void *addr = kheap_start_addr + total_used_size;

    total_used_size += size;

    return addr;
}

/**
 * Returns the largest free memory block (Worst Fit Algorithm).
 */
heap_block_t *worst_fit(uint32_t size) {
    heap_block_t *best = NULL,
                 *temp = head;

    while (temp) {
        if (temp->metadata.is_free && temp->metadata.size >= (uint32_t)size) {
            if (!best || temp->metadata.size > best->metadata.size) {
                best = temp;
            }
        }

        temp = temp->next;
    }

    return best;
}

/**
 * Allocates a new heap block at the end of the heap.
 */
heap_block_t *allocate_new_block(uint32_t size) {
    heap_block_t *new_block = (heap_block_t *)kbrk(sizeof(heap_block_t));

    if (!new_block) {
        return NULL;
    }

    new_block->metadata.is_free = FALSE;
    new_block->metadata.size = size;
    new_block->data = kbrk(size);
    new_block->next = NULL;

    if (!head) {
        head = new_block;
    } else {
        heap_block_t *temp = head;

        while (temp->next) {
            temp = temp->next;
        }

        temp->next = new_block;
    }

    return new_block;
}

/**
 * Allocates memory. Uses worst-fit if possible; otherwise, expands heap.
 */
void *kmalloc(uint32_t size) {
    if (size <= 0) {
        return NULL;
    }

    heap_block_t *block = worst_fit(size);

    if (block) {
        block->metadata.is_free = FALSE;
        return block->data;
    }

    block = allocate_new_block(size);

    return block ? block->data : NULL;
}

/**
 * Allocates and zeroes out memory.
 */
void *kcalloc(uint32_t n, uint32_t size) {
    if (n <= 0 || size <= 0) {
        return NULL;
    }

    void *mem = kmalloc(n * size);

    if (mem) {
        memset(mem, 0, n * size);
    }

    return mem;
}

/**
 * Resizes a previously allocated block.
 */
void *krealloc(void *ptr, uint32_t size)
{
    if (!ptr) {
        return kmalloc(size);
    }

    if (size <= 0) {
        return NULL;
    }

    heap_block_t *temp = head;

    while (temp) {
        if (temp->data == ptr) {
            heap_block_t *new_block = allocate_new_block(size);

            if (!new_block) {
                return NULL;
            }

            int copy_size = (temp->metadata.size > (uint32_t)size) ? (uint32_t)size : temp->metadata.size;
            memcpy(new_block->data, ptr, copy_size);

            temp->metadata.is_free = TRUE;
            return new_block->data;
        }

        temp = temp->next;
    }

    return NULL;
}

/**
 * Frees a previously allocated block.
 */
void kfree(void *addr) {
    heap_block_t *temp = head;
    while (temp) {
        if (temp->data == addr) {
            temp->metadata.is_free = TRUE;
            return;
        }

        temp = temp->next;
    }
}
