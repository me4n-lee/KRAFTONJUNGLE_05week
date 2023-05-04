#include <stdio.h>

int main() 
{
    unsigned int x = 5;
    unsigned int *y = &x; // 변수 y의 타입을 unsigned int 포인터로 명시합니다.
    unsigned int *p = y; // y에 0을 더하는 것은 불필요합니다. 직접 y를 할당하면 됩니다.

    printf("%u", *p);

    return 0; // main 함수의 반환 값을 명시합니다.
}