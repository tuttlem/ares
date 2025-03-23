#include <string.h>
#include <kernel.h>
#include <device.h>

#define MAX_DEVICES 32

device_t* device_registry[MAX_DEVICES];

int device_count = 0;

void device_register(device_t* dev) {
    if (device_count < MAX_DEVICES) {
        device_registry[device_count++] = dev;
    }
}

device_t* device_find_by_name(const char* name) {
  for (int i = 0; i < device_count; i++) {
    if (!strcmp(name, device_registry[i]->name)) {
      return device_registry[i];
    }
  }

  return NULL;
}