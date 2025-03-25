#include <ares/device.h>
#include <ares/drivers.h>
#include <ares/string.h>

static int null_read(device_t* dev, char* buf, int len) {
    (void)dev; (void)buf; (void)len;
    return 0;  // nothing to read
}

static int null_write(device_t* dev, const char* buf, int len) {
    (void)dev; (void)buf;
    return len;  // pretend we wrote everything
}

static device_t null_device = {
    .name = "null",
    .type = DEVICE_CHAR,
    .read = null_read,
    .write = null_write,
    .driver_data = NULL,
    .next = NULL
};

int null_driver_init() {
    device_register(&null_device);
    return 0;
}

driver_t _ares_null_driver = {
    .name = "null",
    .init = null_driver_init,
    .term = NULL
};