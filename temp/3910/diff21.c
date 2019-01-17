#include "answers.h"
#import "drivers/diff21.c"

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
    return 1;
}


