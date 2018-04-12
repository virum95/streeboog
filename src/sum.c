#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int SIZE = 100;

int main(int argc, char *argv[]) {

    int a[SIZE];
    int i;
    int sum = 0;
#pragma omp parallel for
    for (i = 0; i < SIZE; ++i) {
        a[i] = i+1;
    }
    /************************/
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i < SIZE; i++) {
        sum = sum + a[i];
    }
    printf("sum: %i\n", sum);
    return 0;
}