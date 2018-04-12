//
// Created by virum on 3/7/18.
//

#include <stdio.h>
#include <string.h>
#include <openssl/md5.h>

#define SIZE 16

int compute_hash(char *str, unsigned char mdString[33]) {
    unsigned char digest[SIZE];
    MD5_CTX ctx;
    int i;

    MD5_Init(&ctx);
    MD5_Update(&ctx, str, strlen(str));
    MD5_Final(digest, &ctx);

    for (i = 0; i < SIZE; i++)
        sprintf(&mdString[i * 2], "%02x", (unsigned int) digest[i]);

    return 0;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    size_t len;
    char line[1024];
    if (argc == 3)
    {
        fp = fopen(argv[1], "r");
        //Checks if file is empty
        if (fp == NULL)
        {
            return 1;
        }
        while (fgets(line, 1024, fp))
        {
            len = strlen(line);
            line[len - 1] = '\0';
            char hashLine[SIZE*2 + 1];
            compute_hash(line, hashLine);
//            printf("%s\n", hashLine);
            if (strcmp(hashLine, argv[2]) == 0)
            {
                printf("Password found!: *%s*", line);
                break;
            }
        }
    }
    else
    {
        printf("Error, usage: %s <string> <hash>\n", argv[0]);
        return -1;
    }

    return 0;
}
