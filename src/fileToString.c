#include "fileToString.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int FileLength(FILE * fpointer){
    unsigned int length;
    fseek(fpointer, 0L, SEEK_END);
    length = ftell(fpointer);
    rewind(fpointer);

    return length;
}

char * FileToString(char * path) {
    FILE * fpointer = fopen(path, "r");
    int fileLength = FileLength(fpointer);
    char * outString = malloc(fileLength * sizeof(char) + 1);
    strcpy(outString, "\0");
    char tempString[150];

    printf("%s\n", outString);

    while(fgets(tempString, 150, fpointer)){
        strcat(outString, tempString);
    }

    return outString;
}
