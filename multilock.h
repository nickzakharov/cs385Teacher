#define spinlock

#ifdef spinlock
#include "uspinlock.h"
#define lock_t spinlock_t
#define lock_init spinlock_init
#define lock_acquire spinlock_acquire
#define lock_release spinlock_release
#endif

#ifdef ticketlock
#include "ticketlock.h"
#define lock_t ticketlock_t
#define lock_init ticketlock_init
#define lock_acquire ticketlock_acquire
#define lock_release ticketlock_release
#endif

#ifdef waitlock
#include "waitlock.h"
#define lock_t waitlock_t
#define lock_init waitlock_init
#define lock_acquire waitlock_acquire
#define lock_release waitlock_release
#endif
