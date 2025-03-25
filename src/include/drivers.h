
/*
 * Ares 64-bit Operating System
 *
 * Driver management
 */

#ifndef __ares_drivers_h_

#define __ares_drivers_h_


typedef struct driver {
  const char *name;

  int (*init)(void);
  void (*term)(void);

  struct driver* next;
} driver_t;

/**
 * Adds the static "well known" drivers into the registry
 */
void drivers_register_static(void);

/**
 * Initialize all of the registered drivers
 */
void drivers_init_all(void);

/**
 * Terminate all of the registered drivers
 */
void drivers_term_all(void);

/**
 * Register a driver
 */
int driver_register(driver_t *drv);

#endif /* __ares_drivers_h_ */