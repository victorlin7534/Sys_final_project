#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "drivers/lastDigit.c"

int passed = 0;
int tested = 0;
int test(int a, int b, int expected){

    int ans = lastDigit(a,b);
    if ( ans == expected){
        printf("PASSED--");
        passed++;
    }
    else{
        printf("FAILED--");
    }
    tested++;
    printf("lastDigit(%d,%d)\nANSWER:%d\nEXPECTED:%d\n\n",a,b,ans,expected);
    return 1;
}

int main(){
  printf("RUNNING: lastDigit(a,b)\n\n");
  test(20,2,0);
  test(114,4,1);
  test(50,50,1);
  test(114,113,0);
  test(223,332,0);
  printf("%d/%d CASES PASSED\n",passed,tested);
    
  int fileint = open("output", O_CREAT | O_RDWR,0644);
  char * passstr = malloc(1);
  sprintf(passstr, "%d", passed);
  write(fileint, passstr, 1);
  close(fileint);
  return 1;

}


