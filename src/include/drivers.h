
/*
 * Ares 64-bit Operating System
 *
 * Driver management
 */

#ifndef __ares_drivers

#define __ares_drivers


typedef struct {
  const char *name;

  int (*init)(void);
  void (*term)(void);
} driver_t;

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

#endif /* __ares_drivers */