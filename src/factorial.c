#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

    long num = strtol(argv[1], NULL, 10);
    int a[num];
    int i;
    int64_t fact = 1;
#pragma omp parallel for
    for (i = 0; i < num; ++i){
        a[i] = i+1;
    }
    /************************/
#pragma omp parallel for reduction(*:fact)
    for (i = 0; i < num; i++) {
        fact = fact * a[i];
    }
    printf("Factorial of %i: %lld\n",num, fact);
    return 0;
}