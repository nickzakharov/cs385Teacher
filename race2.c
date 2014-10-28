#include"types.h"
#include"user.h"
#include"lock.h"

volatile int shared = 0;
volatile int start = 0;
volatile int done = 0;

lock_t lock;


void f(void) {
  int i;
  while(!start);

  for(i=0;i<100000;i++) {
    lock_acquire(&lock);

    int temp = shared;
    int j;
    for(j=0;j<100;j++);
    shared=temp+1;

    lock_release(&lock);
  }

  done = 1;

}

int main(int argc, char** argv) {
  thread_create(f);
  lock_init(&lock);

  start = 1;

  int i;
  for(i=0;i<100000;i++) {
    lock_acquire(&lock);

    int temp = shared;
    int j;
    for(j=0;j<100;j++);
    shared=temp+1;

    lock_release(&lock);
  }
 
  while(!done);
  printf(1,"Shared is %d\n",shared);

  exit();
  return 0;
}
