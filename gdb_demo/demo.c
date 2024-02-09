#include <stdio.h>
#include <stdlib.h>

int func1(int a, int b)
{
    return a + b;
}


int main()
{
    int a = 10;
    int b = 20;
    int c = func1(a, b);
    printf("c = %d\n", c);
    return 0;
}