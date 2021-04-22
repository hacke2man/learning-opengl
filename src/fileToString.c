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
    char * outString = malloc(FileLength(fpointer) * sizeof(char));
    char tempString[150];

    while(fgets(tempString, 150, fpointer))
        strcat(outString, tempString);

    return outString;
}
