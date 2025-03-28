
/*
 * Ares 64-bit Operating System
 *
 * Device management
 */

#ifndef __ares_device_h_

#define __ares_device_h_

typedef enum {
    DEVICE_CHAR,
    DEVICE_BLOCK,
    DEVICE_UNKNOWN
} device_type_t;

typedef struct device {
    const char* name;
    device_type_t type;

    int (*read)(struct device* dev, char* buf, int len);
    int (*write)(struct device* dev, const char* buf, int len);

    void* driver_data; // Device-specific data (keyboard state, disk sector info, etc.)

    struct device* next;
} device_t;

void device_register(device_t* dev);
device_t* device_find_by_name(const char* name);

#endif /* __ares_device_h_ */