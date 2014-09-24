#include"types.h"
#include"user.h"
int main(int argc, char** argv) {
  int i;

  char* chunks[10];
  for(i=0;i<10;i++) {
    chunks[i]=malloc(1024*1024);
    if(!chunks[i]) {
      printf(1,"Uh-oh, couldn't reserve any more RAM!\n");
      exit();
    }
    memset(chunks[i],i,1024*1024);
  }

  for(i=0;i<10;i++) {
    if(chunks[i][i*100]!=i) {
      printf(1,"Uh-oh, chunk %d doesn't contain all %d's\n",i,i);
      exit();
    }
  }

  exit();
}
