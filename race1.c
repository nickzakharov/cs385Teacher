#include"types.h"
#include"user.h"


volatile int shared = 0;
volatile int start = 0;
volatile int ready = 0;
volatile int done = 0;

void f(void) {
  int i;
  while(!start);
  ready=1;
  asm volatile("" : : : "memory");

  for(i=0;i<100000;i++) {
    shared++;
  }

  done = 1;

}

int main(int argc, char** argv) {
  thread_create(f);
  
  start = 1;
  asm volatile("" : : : "memory");
  while(!ready);

  int i;
  for(i=0;i<100000;i++) {
    shared++;
  }
 
  while(!done);
  printf(1,"race1 shared is %d\n",shared);

  exit();
  return 0;
}
