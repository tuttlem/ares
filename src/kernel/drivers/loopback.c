#include <ares/device.h>
#include <ares/drivers.h>
#include <ares/string.h>
#include <ares/types.h>
#include <ares/heap.h>

#define LOOPBACK_BUF_SIZE 1024

typedef struct {
    char buffer[LOOPBACK_BUF_SIZE];
    int head;
    int tail;
} loopback_data_t;

static int loopback_read(device_t* dev, char* buf, int len) {
    loopback_data_t* lpb = dev->driver_data;
    int count = 0;

    while (lpb->head != lpb->tail && count < len) {
        buf[count++] = lpb->buffer[lpb->tail];
        lpb->tail = (lpb->tail + 1) % LOOPBACK_BUF_SIZE;
    }

    return count;
}

static int loopback_write(device_t* dev, const char* buf, int len) {
    loopback_data_t* lpb = dev->driver_data;
    int count = 0;

    while (count < len) {
        int next = (lpb->head + 1) % LOOPBACK_BUF_SIZE;
        if (next == lpb->tail) break;  // buffer full
        lpb->buffer[lpb->head] = buf[count++];
        lpb->head = next;
    }

    return count;
}

static device_t loopback_device = {
    .name = "loopback",
    .type = DEVICE_CHAR,
    .read = loopback_read,
    .write = loopback_write,
    .driver_data = NULL,
    .next = NULL
};

int loopback_driver_init() {
    loopback_data_t* data = kmalloc(sizeof(loopback_data_t));
    data->head = 0;
    data->tail = 0;
    loopback_device.driver_data = data;

    device_register(&loopback_device);
    return 0;
}

driver_t _ares_loopback_driver = {
    .name = "loopback",
    .init = loopback_driver_init,
    .term = NULL,
};