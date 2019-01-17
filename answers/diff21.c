#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "drivers/diff21.c"

int passed = 0;
int tested = 0;
int test(int a, int expected){

    int ans = diff21(a);
    if ( ans == expected){
        printf("PASSED--");
        passed++;
    }
    else{
      printf("FAILED--");
    }
    tested++;
    printf("diff21(%d)\nANSWER:%d\nEXPECTED:%d\n\n",a,ans,expected);
    return 1;
}

int main(){
  printf("RUNNING: diff21(a)\n\n");
  test(19,2);
  test(10,11);
  test(22,2);
  test(-1,21);
  test(-22,43);
  printf("%d/%d CASES PASSED\n",passed,tested);
  
  int fileint = open("output", O_CREAT | O_RDWR | O_TRUNC, S_IWUSR | S_IXUSR | S_IRUSR);
  char * passstr = malloc(999);
  sprintf(passstr, "%d", passed);
  write(fileint, passstr, 999);
  close(fileint);
  return 1;

}


