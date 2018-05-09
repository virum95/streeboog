#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define SIZE 16

unsigned long
doHash(char *key, size_t len) {
    uint32_t hash, i;
    for (hash = i = 0; i < len; ++i)
    {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
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


int main(int argc, char *argv[]) {
    unsigned long hash;
    if (argc == 2)
    {
        printf("%s, %i\n", argv[1], strlen(argv[1]));
        hash = doHash(argv[1], strlen(argv[1]));
        printf("%lu", hash);
    }
    else
    {
        printf("Error, usage: %s <string>\n", argv[0]);
        return -1;
    }

    return 0;
}
