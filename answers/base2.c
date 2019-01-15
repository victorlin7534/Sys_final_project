#include "answers.h"
#import "../temp/????/base2.c"

int passed = 0;
int tested = 0;
int test(int a, int expected){

  int ans = base2(a);
  if ( ans == expected){
    printf("PASSED--");
    passed++;
  }
  else{
    printf("FAILED--");
  }
  tested++;
  printf("base2(%d)\nANSWER:%d\nEXPECTED:%d\n\n",a,ans,expected);
  return 1;
}

int main(){
  printf("RUNNING: base2(a)\n\n");
  test(0,0);
  test(1,1);
  test(2,10);
  test(99,1100011);
  test(64,1000000);
  printf("%d/%d CASES PASSED\n",passed,tested);
  return 1;
}


