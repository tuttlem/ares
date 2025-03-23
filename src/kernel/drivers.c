
#include "drivers.h"

#include "../arch/x86_64/include/drivers/ps2kbd.h"

#define MAX_DRIVERS 64

static driver_t* registered_drivers[] = {
    &ps2kbd_driver,
};

static int driver_count = 1;

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