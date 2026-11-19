
#include <stdio.h>

int sum (int a, int b);

int
main (void) {

    int total = sum(2, 3);

    printf("%d", total);


    return 0;
}

int sum (int a, int b) {

    return a+b;
}