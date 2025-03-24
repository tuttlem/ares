
#include "drivers.h"

#define MAX_DRIVERS 64

extern driver_t pit_driver;
extern driver_t console_driver;
extern driver_t ps2kbd_driver;

static driver_t* registered_drivers[] = {
    &pit_driver,
    &console_driver,
    &ps2kbd_driver,
};

static int driver_count = 3;

/**
 * Initialize all of the registered drivers
 */
void drivers_init_all(void) {
    for (int i = 0; i < driver_count; i++) {
      if (registered_drivers[i]->init) {
          registered_drivers[i]->init();
      }
    }
}

/**
 * Terminate all of the registered drivers
 */
void drivers_term_all(void) {
    for (int i = 0; i < driver_count; i++) {
        if (registered_drivers[i]->term) {
            registered_drivers[i]->term();
        }
    }
}

/**
 * Register a driver
 */
int driver_register(driver_t *drv) {
    if (driver_count < MAX_DRIVERS) {
        registered_drivers[driver_count ++] = drv;
    }
}