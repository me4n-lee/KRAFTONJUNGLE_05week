// Q 9 - What will be the output of the following program?

#include<stdio.h>

int main(){

    const int i = 0;
    // int i = 0;

    printf("%d\n", i++);
    return 0;

}

// A : Return error

// "++" 연산자는 값을 필요로하며
// const 변수는 변경할 수 없기 때문에 컴파일러가 "i++" 문장에서 오류를 발생시키게 됩니다.