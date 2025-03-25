#ifndef __ares_spinlock_h_

#define __ares_spinlock_h_

#include <types.h>

extern void spin_lock(uint32_t *lock);
extern void spin_unlock(uint32_t *lock);

#endif /* __ares_spinlock_h_ */
