#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/streebog/gost3411-2012.h"
#include <math.h>

#define MIN 4
#define MAX 4
//#define ALPHA "1234567890ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvwxyz"
#define ALPHA "abcdefghijklmnopqrstuvwxyz1234567890"
//#define SECRET "2990e0c0316c9cf51dbc38df4fd50d780fbf3564cbfb3734c3acfd56a7161ed79c99c406420c48bb00930a71884f3acc9febeaddcc2791fc9484b9a60d0b0ba8"
#define SECRET "6385374830"

long get_keyspace(char *alpha, int max) {
    long size = 1;
    for (int i = 0; i < max; ++i)
    {
        size = size * strlen(alpha);
    }
    return size;
}


uint32_t adler32(const void *buf, size_t buflength) {
    const uint8_t *buffer = (const uint8_t *) buf;

    uint32_t s1 = 1;
    uint32_t s2 = 0;

    for (size_t n = 0; n < buflength; n++)
    {
        s1 = (s1 + buffer[n]) % 65521;
        s2 = (s2 + s1) % 65521;
    }
    return (s2 << 16) | s1;
}

unsigned long
doHash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
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
    char *password;


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
    char secret[129] = {0};
    unsigned long hash;
    if (optind > argc)
    {
        hash = (unsigned long) atol(SECRET);
//        strcpy(secret, SECRET);
//        strcat(secret, '\0');
    }
    else
    {
        hash = (unsigned long) atol(argv[optind]);
//        strcpy(secret, argv[optind]);
//        strcat(secret, '\0');
    }
//    printf("Hash-->%lu<--\n", hash);
//    printf("-->%s<--\n", secret);
    int len = (int) strlen(alphabet);
    long keyspace = get_keyspace(alphabet, size);

    int index[size];

    char candidate[size];

    for (int i = 0; i < size; ++i)
    {
        index[i] = 0;
    }
    int j;
    int k;
#pragma omp parallel for private(candidate, index, j, k) shared(found)
    for (long i = 0; i < keyspace; ++i)
    {
        if (found == 0)
        {
            for (k = 1; k <= size; ++k)
            {
                strcpy(candidate, "");
                for (j = k - 1; j >= 0; --j)
                {
                    index[j] = (int) ((i / (int) pow(len, j)) % len);
//                printf("%d\n", index[j]);
                    sprintf(candidate, "%s%c", candidate, alphabet[index[j]]);
                }
//            printf("candidate: --%s--\n", candidate);
//            if (strcmp(compute_hash(candidate), secret) == 0)
                if (doHash(&candidate[0]) == hash)
                {
                    printf("Secret found: **%s**\n", candidate);
                    found = 1;
                }
            }
        }
    }
    if (found == 0)
    {
        printf("Password not found :(");
    }
    return 0;
}
