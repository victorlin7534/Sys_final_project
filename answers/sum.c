#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "drivers/sum.c"

int passed = 0;
int tested = 0;
int test(int a, int b, int expected){

    int ans = sum(a,b);
    if ( ans == expected){
        printf("PASSED--");
        passed++;
    }
    else{
      printf("FAILED--");
    }
    tested++;
    printf("sum(%d,%d)\nANSWER:%d\nEXPECTED:%d\n\n",a,b,ans,expected);
    return 1;
}

int main(){
  printf("RUNNING: sum(a,b)\n\n");
  test(1,2,3);
  test(-99,20,-79);
  test(100,200,300);
  test(-1,-2,-3);
  test(12,22,34);
  printf("%d/%d CASES PASSED\n",passed,tested);
    
  int fileint = open("output", O_CREAT | O_RDWR,0644);
  char * passstr = malloc(1);
  sprintf(passstr, "%d", passed);
  write(fileint, passstr, 1);
  close(fileint);
  return 1;

}


