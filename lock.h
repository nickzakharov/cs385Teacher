typedef struct { 
  int locked;
} lock_t;

void lock_init(lock_t* lock) {}
void lock_acquire(lock_t* lock) {}
void lock_release(lock_t* lock) {}

