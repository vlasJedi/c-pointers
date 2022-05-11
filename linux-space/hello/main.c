#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "helper.h"

void printFileInBinary(void);
char *reallocateTwice(char *sourceStr);
void executeScenario(FILE* file);
int writeToFile(FILE* file, void* val, int dataSize, int count);
int readFromFile(FILE* file, int offset, void* val, int dataSize, int count);
int encodeString(char* srcString, char* encodedString);
int decodeString(char* srcString, char* decodedString);

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
            printf("%s\n", initString);
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

void executeScenario(FILE* file) {
    //char srcString[] = {'H', 'e', 'l', 'l', 'o'};
    char* srcString = "Hello";
    int length = 6;
    char encodedString[length];
    encodeString(srcString, encodedString);
    if (writeToFile(file, encodedString, sizeof(char), length - 1) == -1) {
        printf("Failed to write to file \n");
        return;
    }
    char val[6]; 
    if (readFromFile(file, 0, val, sizeof(char), length - 1) == -1) {
        printf("Failed to read from file \n");
        return;
    }
    printf("Read from file: %s\n", val);
    char decodedString[length];
    decodeString(val, decodedString);
    printf("Decoded value: %s\n", decodedString);
    //char ** tempString;
    //convertToDiffBase(val, 2, tempString, "01");
    //printf("As byte: %s\n", *tempString); 
}

void printFileInBinary(void)
{
    // + means that file will be created if not exists and w will force at first truncating file
    FILE* file = fopen("test.txt", "wb+");
    if (file == NULL) {
        printf("Could not find a file ...\n");
        return;
    }
    executeScenario(file); 
    if (fclose(file) != 0) {
        printf("Failed closing ...\n");
        return;
    }
    printf("Closed with success ...\n");
}

int writeToFile(FILE* file, void* val, int dataSize, int count) {
    if (fwrite(val, dataSize, count, file) == 0) {
        printf("Failed to write any bytes\n");
        return -1;
    } 
    printf("Number of written bytes: %d\n", count);
    if (fflush(file) == 0) {
        printf("Flushed with success to file\n");
        return 0;
    }
    printf("Flush failed to file\n");
    return -1;
}

int readFromFile(FILE* file, int offset, void* val, int dataSize, int count)
{
    if (fseek(file, offset, SEEK_SET) != 0) {
        printf("Could not set read position in the file\n");
        return -1;
    } 
    count = fread(val, dataSize, count, file);
    printf("Number of read items: %d\n", count);
}

int encodeString(char* srcString, char* encodedString) {
    for(int i = 0; i < strlen(srcString); i++) {
        *(encodedString + i) = (*(srcString + i)) + 1;
    }
}

int decodeString(char* srcString, char* decodedString) {
    for(int i = 0; i < strlen(srcString); i++) {
        *(decodedString + i) = (*(srcString + i)) - 1;
    }
}