#include <kernel.h>
#include <device.h>
#include <drivers.h>

device_t* stdout_device = NULL;

void set_stdout_device(device_t* dev) {
    stdout_device = dev;
}

int write_stdout(const char* buf, int len) {
    if (stdout_device && stdout_device->write) {
        return stdout_device->write(stdout_device, buf, len);
    }

    return -1;
}

int write_stdout_char(char ch, int len) {
    char buf[1];
    buf[0] = ch;

    return write_stdout(buf, 1);
}