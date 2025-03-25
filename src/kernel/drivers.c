
#include "drivers.h"

#include <types.h>
#include <heap.h>

static driver_t* driver_registry = NULL;

extern driver_t pit_driver;
extern driver_t console_driver;
extern driver_t ps2kbd_driver;

void drivers_register_static(void) {
    driver_register(&pit_driver);
    driver_register(&console_driver);
    driver_register(&ps2kbd_driver);
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