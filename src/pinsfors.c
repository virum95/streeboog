//
// Created by virum on 3/1/18.
//

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {

#pragma omp parallel for
    int i, j, k, l;
    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < 10; ++k)
            {
                for (int l = 0; l < 10; ++l)
                {
                    printf("%d%d%d%d\n", i, j, k, l);
                }
            }
        }
    }
    return 0;
}