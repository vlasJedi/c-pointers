#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "helper.h"

void printFileInBinary(void);
char *reallocateTwice(char *sourceStr);

// int count and array of pointers to strings
int main(int argc, char *argv[])
{
    //runRepeaterWithExit();
    printFileInBinary();
}

char *reallocateTwice(char *sourceStr)
{
    char *newstr = (char *)malloc((sizeof(char) * strlen(sourceStr)) << 1);
    strcpy(newstr, sourceStr);
    return newstr;
}

int runRepeaterWithExit()
{
    int size = 16;
    const char *exitString = "exit";
    const int exitStringSize = strlen(exitString);
    // include size of zero ending in calculation of length
    char *initString = (char *) malloc(sizeof(char) * size);
    int index = 0;
    char newChar = 0;
    char* concat = appendToString("Some", "string");
    while (1)
    {
        // index will point + 1 which is equal to 0 bit so it the same length
        if (index == exitStringSize && !strncmp(initString, exitString, strlen(exitString)))
        {
            printf("Exiting\n");
            free(initString);
            break;
        }
        // new char available
        if ((newChar = (char)fgetc(stdin)) == '\n')
        {
            printf(strcat(initString, "\n"));
            // put to 0 all string bytes
            memset(initString, 0, strlen(initString));
            index = 0;
            continue;
        }
        if (size == (index + 1))
        {
            printf("Allocating more space\n");
            char *old = initString;
            initString = reallocateTwice(initString);
            free(old);
        }
        *(initString + index) = newChar;
        index++;
    }
    return 0;
}

void printFileInBinary(void)
{
    // + means that file will be created if not exists and w will force at first truncating file
    FILE* file = fopen("test.txt", "wb+");
    if (file == NULL) {
        printf("Could not find a file ...\n");
        return;
    }
    int val = 5;
    int count = fwrite(&val, sizeof(val), 1, file);
    printf("Number of written bytes: %d\n", count);
    val = 0;
    fflush(file);
    fseek(file, 0, SEEK_SET);
    count = fread(&val, sizeof(val), 1, file);
    printf("Number of read bytes: %d\n", count);
    printf("Read from file: %d\n", val);
    if (fclose(file) != 0) {
        printf("Failed closing ...\n");
        return;
    }
    printf("Closed with success ...\n");
}
