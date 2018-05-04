#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

#define SIZE 16

unsigned long
doHash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


int main(int argc, char *argv[]) {
    unsigned long hash;
    if (argc == 2)
    {
        hash = doHash(argv[1]);
        printf("%lu", hash);
    }
    else
    {
        printf("Error, usage: %s <string>\n", argv[0]);
        return -1;
    }

    return 0;
}
