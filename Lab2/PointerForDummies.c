#include <stdio.h>

void testing(int *x)
{               
    *x = *x * 2; // Dereference, then double, test
}

int main(void)
{
    int y = 10;
    int *p = &y;        // Pointer points to adress of y, * is for declaration of pointer not dereference
    testing(&y);        // Pass in adress of Y, since it gets dereferenced in testing()
    printf("%d\n", y);  // Print value of Y
    printf("%p\n", &y); // Print adress of Y
    printf("%p\n", p);  // Print what is stored in P
    printf("%d", *p);   // Print dereferenced P
}
