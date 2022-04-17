#include <stdio.h>

int main(){
    int a = 0x1;
    if(a) {
        int b1 = 0;
        printf("This is basic block 2\n");
    }
    else {
        printf("This is basic block 2\n");
    }
    a = 10;
}