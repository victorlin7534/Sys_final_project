#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "drivers/gcf.c"

int passed = 0;
int tested = 0;
int test(int a, int b, int expected){

  int ans = gcf(a,b);
  if ( ans == expected){
    printf("PASSED--");
    passed++;
  }
  else{
    printf("FAILED--");
  }
  tested++;
  printf("gcf(%d,%d)\nANSWER:%d\nEXPECTED:%d\n\n",a,b,ans,expected);
  return 1;
}

int main(){
  printf("RUNNING: gcf(a,b)\n\n");
  test(1,2,1);
  test(999,6,3);
  test(50,50,50);
  test(49,7,7);
  test(1238,88,2);
  printf("%d/%d CASES PASSED\n",passed,tested);

  int fileint = open("output", O_CREAT | O_RDWR,0644);
  char * passstr = malloc(1);
  sprintf(passstr, "%d", passed);
  write(fileint, passstr, 1);
  close(fileint);
  return 1;
}


