// Q 2 - What is the output of the following program?

#include<stdio.h>

int main(){ 
   int a[] = {1,2}, *p = a;
   
   printf("%d\n", p[1]); 
}

// A : 2

// p가 기본 주소를 가지고 있으므로 a처럼 p를 사용하여 배열에 접근할 수 있습니다.
// 출력 결과는 2이며, 이는 p가 a의 기본 주소를 가지고 있어서
// p를 사용하여 배열에 접근할 수 있기 때문입니다.