#include<stdio.h>

int main() 
{
   unsigned x = 5, *y=&x, *p = y+0; 

   printf("%u",*y);
   return 0;
}