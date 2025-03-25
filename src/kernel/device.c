
#include <device.h>

#include <string.h>
#include <kernel.h>
#include <heap.h>

static device_t* device_registry = NULL;

void device_register(device_t* dev) {
    if (!device_registry) {
        device_registry = dev;
        dev->next = NULL;
    } else {
        device_t* current = device_registry;

        while (current->next) {
            current = current->next;
        }

        current->next = dev;
        dev->next = NULL;
    }
}

device_t* device_find_by_name(const char* name) {
    device_t* current = device_registry;

    while (current) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }

        current = current->next;
    }

    return NULL;
}