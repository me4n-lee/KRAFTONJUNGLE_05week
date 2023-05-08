// Q 5 - What is the output of the following statement?

#include <stdio.h>

int main(){

    printf("%d\n", -1<<1);

}

// A : -2

// 음수는 양수의 2의 보수로 저장됩니다.
// 시프트한 후에 결과는 1110이며, 이는 -2와 동일합니다.