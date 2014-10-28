#include"types.h"
#include"user.h"


int shared = 0;
volatile int start = 0;
volatile int done = 0;


void f(void) {
  int i;
  while(!start);

  for(i=0;i<1000000000;i++) {
    shared++;
  }

  done = 1;

}

int main(int argc, char** argv) {
  thread_create(f);
  
  start = 1;

  int i;
  for(i=0;i<1000000000;i++) {
    shared++;
  }
 
  while(!done);
  printf(1,"race1b shared is %d\n",shared);

  exit();
  return 0;
}
