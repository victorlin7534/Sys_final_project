#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#import "../diff21.c"

int passed = 0;
int tested = 0;

int test(int a, int expected){
  if (diff21(a) == expected){
    printf("PASSED\n", a );
    passed ++;
  }
  else{
    printf("FAILED\n", a );
  }
  printf("diff21(%d),EXPECTED: %d, ACTUAL: %d\n",a,expected,diff(a));
  tested++;
}

int main(int x){
  test(19,2);
  test(10,11);
  test(21,0);

  if (passed != tested){

  }
  return 0;
}


