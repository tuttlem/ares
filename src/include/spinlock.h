#ifndef __ares_spinlock_h_

#define __ares_spinlock_h_

#include <types.h>

extern void spin_lock(u32 *lock);
extern void spin_unlock(u32 *lock);

#endif /* __ares_spinlock_h_ */
