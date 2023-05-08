// Q 2 - What is the output of the following program?

#include<stdio.h>

int main(){ 
   int a[] = {1,2}, *p = a;
   
   printf("%d\n", p[1]); 
}

// as ‘p’ holds the base address then we can access array using ‘p’ 
// just like with ‘a’