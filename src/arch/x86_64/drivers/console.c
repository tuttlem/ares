#include <heap.h>
#include <types.h>
#include <device.h>
#include <drivers.h>

#include <io.h>

static uint16_t cur_x = 0, cur_y = 0;
static uint16_t *console_buffer = (uint16_t*)0xB8000;

/* Moves the cursor along one character */
void console_cursor_move() {
   uint16_t loc = cur_y * 80 + cur_x;

   outb(0x03D4, 14);
   outb(0x03D5, loc >> 8);

   outb(0x03D4, 15);
   outb(0x03D5, loc);
}

/* Scrolls the console by 1 line of text */
void console_scroll() {
   uint8_t attr = 15;
   uint16_t blank = 0x20 | (attr << 8);

   if (cur_y >= 25) {
      int i;

      for (i = 0; i < (24*80); i++) {
         console_buffer[i] = console_buffer[i + 80];
      }

      for (i = (24*80); i < (25*80); i++) {
         console_buffer[i] = blank;
      }

      cur_y = 24;
   }
}

/* Writes a character onto the console */
void console_put(char c) {
   uint8_t attr = 15;
   uint16_t ch = attr << 8;
   uint16_t *location;

   if (c == 0x08 && cur_x) {
      cur_x --;
   } else if (c == 0x09) {
      cur_x = (cur_x + 8) & ~(8 - 1);
   } else if (c == '\r') {
      cur_x = 0;
   } else if (c == '\n') {
      cur_x = 0;
      cur_y ++;
   } else if (c >= ' ') {
      location = console_buffer + (cur_y * 80 + cur_x);
      *location = c | ch;
      cur_x ++;
   }

   if (cur_x >= 80) {
      cur_x = 0;
      cur_y ++;
   }

   console_scroll();
   console_cursor_move();
}

/* Clears the console */
void console_clear() {
   uint16_t blank = 0x20 | (15 << 8);

   int i;
   for (i = 0; i < (80*25); i ++) {
      console_buffer[i] = blank;
   }

   cur_x = 0;
   cur_y = 0;
   console_cursor_move();
}

/* Prints a string of text to the console */
void console_puts(const char *s) {
   int i = 0;
   while (s[i]) {
      console_put(s[i++]);
   }
}

static int console_write(device_t* dev, const char* buf, int len) {
    for (int i = 0; i < len; i ++) {
        console_put(buf[i]);
    }

    return len;
}

int console_driver_init() {
    device_t* console_device = kmalloc(sizeof(device_t));

    console_device->name = "console0";
    console_device->type = DEVICE_CHAR;
    console_device->read = NULL;
    console_device->write = console_write;
    console_device->driver_data = NULL;
    console_device->next = NULL;

    device_register(console_device);

    return 0;
}

void console_driver_term() {
}

driver_t _ares_console_driver = {
    .name = "console",
    .init = console_driver_init,
    .term = console_driver_term
};