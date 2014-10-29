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

  for(i=0;i<1000000000;i++) {
    lock_acquire(&lock);
    shared++;
    lock_release(&lock);
  }

  done = 1;

}

int main(int argc, char** argv) {
  thread_create(f);
  lock_init(&lock);

  start = 1;

  int i;
  for(i=0;i<1000000000;i++) {
    lock_acquire(&lock);
    shared++;
    lock_release(&lock);
  }
 
  while(!done);
  printf(1,"race2 shared is %d\n",shared);

  exit();
  return 0;
}
