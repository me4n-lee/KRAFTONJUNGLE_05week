// Q 1 - What is the output of the below code snippet?

#include<stdio.h>

int main() 
{
   unsigned x = 5, *y=&x, *p = y+0; 

   printf("%u",*y);
   return 0;
}

// A: 5

// 5, as p holds the address of x which is y+0

// #include<stdio.h>

// main() 
// {
//    unsigned x = 5, y=&x, *p = y+0; 

//    printf("%u",*p);
// }