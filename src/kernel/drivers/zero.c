
#include <ares/device.h>
#include <ares/drivers.h>
#include <ares/string.h>

static int zero_read(device_t* dev, char* buf, int len) {
    (void)dev;
    memset(buf, 0, len);  // return all zeros
    return len;
}

static int zero_write(device_t* dev, const char* buf, int len) {
    (void)dev; (void)buf;
    return len;
}

static device_t zero_device = {
    .name = "zero",
    .type = DEVICE_CHAR,
    .read = zero_read,
    .write = zero_write,
    .driver_data = NULL,
    .next = NULL
};

int zero_driver_init() {
    device_register(&zero_device);
    return 0;
}

driver_t _ares_zero_driver = {
    .name = "zero",
    .init = zero_driver_init,
    .term = NULL
};
