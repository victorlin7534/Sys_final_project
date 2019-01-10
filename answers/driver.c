#include <stdio.h>
#include <stdlib.h>
#import <../stub.c>

int passed = 0;
int tested = 0;

int test(void * params,void (*greeter)(void * stuffs), char * fxheader, int expected){
  char * ret_str = "";
  if (sum(a,b) == expected){
    strcat(ret_str,"PASSED: ");
    passed++;
  }
  else{
    strcat(ret_str,"FAILED: ");
  }
  tested++;
  printf("FUNCTION:%s, \n",);
}




