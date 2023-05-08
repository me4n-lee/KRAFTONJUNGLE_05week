// Q:1 Predict the output of following program?

#include <stdio.h>

int main(){

    char arr[100];

    printf("%d\n", scanf("%s", arr));

    return 1;

}

// A : 1

// C 언어에서 scanf 함수는 성공적으로 읽은 입력의 개수를 반환합니다.
// 이 프로그램은 입력한 문자열의 길이에 해당하는 숫자를 출력합니다.