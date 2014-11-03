#include"types.h"
#include"user.h"
#include"multilock.h"

volatile int shared = 0;
volatile int start = 0;
volatile int ready = 0;
volatile int done = 0;

lock_t lock,lock2;

volatile int thread_count = 0;

void f(void) {
  int i;
  int id;
  lock_acquire(&lock);
  id = thread_count++;  
  lock_release(&lock);

  while(!start);
  ready=1;
  asm volatile("" : : : "memory");

  for(i=0;i<100;i++) {
    if(id<5)
      lock_acquire(&lock);
    else
      lock_acquire(&lock2);

    int j;
    int temp = shared;
    if(id%5) 
      for(j=0;j<1000;j++);
    else
      for(j=0;j<1000000;j++);


    if(id<5) {
      shared = temp + 1;      
      lock_release(&lock);
    }
    else
      lock_release(&lock2);
  }

  lock_acquire(&lock);
  done++;
  lock_release(&lock);
}

int main(int argc, char** argv) {
  lock_init(&lock);
  lock_init(&lock2);

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

  printf(1,"race4 shared is %d\n",shared);

  exit();
  return 0;
}
