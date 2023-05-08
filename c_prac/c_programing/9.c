// Q 9 - What will be the output of the following program?

#include<stdio.h>

int main(){

    const int i = 0;
    // int i = 0;

    printf("%d\n", i++);
    return 0;

}

// 이 코드는 C 언어로 작성되었습니다.
// 코드를 실행하려고 하면 컴파일 에러가 발생합니다.
// 왜냐하면 const int i 변수가 상수로 선언되었기 때문입니다. 
// 상수는 한 번 선언되면 변경할 수 없습니다. 
// 그러나 코드에서 i++를 사용하여 상수 값을 변경하려고 시도하고 있습니다. 
// 이로 인해 컴파일 에러가 발생합니다.