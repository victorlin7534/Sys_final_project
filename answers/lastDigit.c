#include "answers.h"
#import "../temp/????/lastDigit.c"

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
    return 1;
}


