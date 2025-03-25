
#include "drivers.h"

#include <types.h>
#include <heap.h>

static driver_t* driver_registry = NULL;

extern driver_t _ares_pit_driver;
extern driver_t _ares_console_driver;
extern driver_t _ares_ps2kbd_driver;
extern driver_t _ares_null_driver;
extern driver_t _ares_zero_driver;
extern driver_t _ares_loopback_driver;


void drivers_register_static(void) {
    driver_register(&_ares_pit_driver);
    driver_register(&_ares_console_driver);
    driver_register(&_ares_ps2kbd_driver);
    driver_register(&_ares_null_driver);
    driver_register(&_ares_zero_driver);
    driver_register(&_ares_loopback_driver);
}

/**
 * Initialize all of the registered drivers
 */
void drivers_init_all(void) {
    driver_t* current = driver_registry;

    while (current) {
        if (current->init) {
            current->init();
        }

        current = current->next;
    }
}

/**
 * Terminate all of the registered drivers
 */
void drivers_term_all(void) {
    driver_t* current = driver_registry;

    while (current) {
        if (current->term) {
            current->term();
        }

        current = current->next;
    }
}

/**
 * Register a driver
 */
int driver_register(driver_t *drv) {
    drv->next = NULL;

    if (!driver_registry) {
        driver_registry = drv;
    } else {
        driver_t* current = driver_registry;

        while (current->next) {
            current = current->next;
        }

        current->next = drv;
    }
}