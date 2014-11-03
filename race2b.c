#include"types.h"
#include"user.h"
#include"multilock.h"

volatile int shared = 0;
volatile int start = 0;
volatile int ready = 0;
volatile int done = 0;

lock_t lock;

void f(void) {
  int i;
  while(!start);
  ready=1;
  asm volatile("" : : : "memory");

  for(i=0;i<100000;i++) {
    lock_acquire(&lock);
    shared++;
    lock_release(&lock);
  }

  lock_acquire(&lock);
  done++;
  lock_release(&lock);
}

int main(int argc, char** argv) {
  lock_init(&lock);

  thread_create(f);
  thread_create(f);
  thread_create(f);
  thread_create(f);
  thread_create(f);
  thread_create(f);
  thread_create(f);
  thread_create(f);
  thread_create(f);
  thread_create(f);
  
  int i;
  for(i=0;i<100000000;i++);

  start = 1;
  asm volatile("" : : : "memory");

  while(done!=10);

  printf(1,"race2b shared is %d\n",shared);

  exit();
  return 0;
}
