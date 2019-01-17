#include "answers.h"
#import "drivers/gcf.c"

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
    return 1;
}


