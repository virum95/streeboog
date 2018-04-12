#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char line[1024];
    FILE *fp;
    size_t len;

    if (argc == 2) {
         fp = fopen(argv[1],"r");
         //Checks if file is empty
         if( fp == NULL ) {                       
           return 1;
         }
    } else  {
         return 1;
    }


    while( fgets(line,1024,fp) ) {
        len = strlen(line);
        line[len-1] = '\0'; 
        printf("candidate: ***%s***\n", line);
    }

    return 0;
}
