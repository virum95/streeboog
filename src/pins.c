//
// Created by virum on 3/1/18.
//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MIN 4
#define MAX 4
#define ALPHA "1234567890"

int get_keyspace(char* alpha, int min, int max){
    return strlen(alpha) + min + max;
}

int main(int argc, char *argv[]) {


    int keyspace  = get_keyspace(ALPHA, MIN, MAX);
    printf("%u", strlen(ALPHA));


#pragma omp parallel for
    for (int i = 0; i < 1000000; ++i)
    {
        printf("%0*d\n", 4, i);
    }
    return 0;
}

