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

  for(i=0;i<1000;i++) {
    lock_acquire(&lock);

    int j;
    int temp = shared;
    for(j=0;j<10000;j++);

    shared = temp + 1;
    lock_release(&lock);
  }

  done = 1;

}

int main(int argc, char** argv) {
  lock_init(&lock);

  thread_create(f);

  int i;
  for(i=0;i<100000000;i++);

  start = 1;

  for(i=0;i<1000;i++) {
    lock_acquire(&lock);

    int j;
    int temp = shared;
    for(j=0;j<10000;j++);
    shared = temp + 1;
    lock_release(&lock);
  }
 
  while(!done);
  printf(1,"race3 shared is %d\n",shared);

  exit();
  return 0;
}
