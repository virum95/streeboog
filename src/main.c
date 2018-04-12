#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int SIZE = 100;

int main(int argc, char *argv[]) {

    int a[SIZE];
    int b[SIZE];
    int i;
    int sum = 0;
#pragma omp parallel for
    for (i = 0; i < SIZE; ++i) {
        a[i] = i;
        b[i] = SIZE - i - 1;
    }
    /************************/
    int tmp;
#pragma opm parallel for private(tmp)
    for (i = SIZE; i > 0; i--) {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
    int r = rand() % SIZE;
    printf("%i - %i\n", a[r], b[r]);
    return 0;
}