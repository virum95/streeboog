#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/streebog/gost3411-2012.h"
#include <memory.h>
#include <math.h>

#define MIN 4
#define MAX 4
//#define ALPHA "1234567890ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvwxyz"
#define ALPHA "abcdefghijklmnñopqrstuvwxyz"
#define SECRET "2990e0c0316c9cf51dbc38df4fd50d780fbf3564cbfb3734c3acfd56a7161ed79c99c406420c48bb00930a71884f3acc9febeaddcc2791fc9484b9a60d0b0ba8"

#include <omp.h>

long get_keyspace(char *alpha, int max) {
    long size = 1;
    for (int i = 0; i < max; ++i)
    {
            size = size*strlen(alpha);
    }
    return size;
}

int main(int argc, char *argv[]) {

    if (argc == 1)
    {
        printf("Enter a value.\n");
        return 1;
    }
    char *avalue = NULL;
    char *svalue = NULL;
    char *alphabet;
    int size;
    int found = 0;
    char * password;


    int ch;
    while ((ch = getopt(argc, argv, "a:d:s:")) != -1)
    {
        switch (ch)
        {
            case 'a':
                avalue = optarg;
                break;
            case 's':
                svalue = optarg;
                break;
            case 'd':
                printf("Option d selected %s\n", optarg);
                break;
            default:
                printf("Insert a command.\n");
        }
    }

    alphabet = avalue != NULL ? strdup(avalue) : ALPHA;
    size = svalue != NULL ? atoi(svalue) : MAX;
    char secret[128];
    if (optind > argc)
    {
        strcpy(secret,SECRET);
    }
    else
    {
        strcpy(secret, argv[optind]);
    }

    int len = strlen(alphabet);
    long keyspace = get_keyspace(alphabet , size);

    int index[size];

    char candidate[size];

    for (int i = 0; i < size; ++i)
    {
        index[i] = 0;
    }
#pragma omp parallel for private(candidate, index, j)
    for (long i = 0; i < keyspace; ++i)
    {
        if (found == 0)
        {
            strcpy(candidate, "");
            for (int j = size - 1; j >= 0; --j)
            {
                index[j] = (i / (int) pow(len, j)) % len;
                sprintf(candidate, "%s%c", candidate, alphabet[index[j]]);
            }
            if (strcmp(compute_hash(candidate), secret) == 0)
            {
                printf("Secret found: **%s**\n", candidate);
                found = 1;
//                return 0;
            }
        }
    }
    if (found == 1)
    {
        printf("Password not found :(");
    }
    return 0;
}
