#include <stdio.h>
#include "linked-list.h";
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

void printByteIntAsHex(int number, char* base);
void convertToDiffBase(int number, int base, char* result, char* space);

int main(int count, char* argv[])
{
    int x1 = 1;
    int x2 = 2;

    // By default C uses defula 'C' locale which is reduced in range
    
    printf("Number of arguments is: %d\n\r", count);
    
    const char * locale = setlocale(LC_ALL, NULL);
    printf("Current locale is: '%s'\n\r", locale);

    // looks like windows by default use Windows CP1251 as possibly it has reduced length of string storaging
    locale = setlocale(LC_ALL, ".UTF-8");
    printf("Updated system locale so stdin and stdout will use this encoding: '%s'\n\r", locale);

    printf("Number of arguments is: %d\n\r", count);

    const char* prefix = "Arg index is: %d";
    for (int i = 0; i < count; i++) {
        // first indirection to get address from array index and then from that address actual string
        printf("Arg index is: %d and value: ", i);
        printf(argv[i]);
        printf("\n");
    }

    printf("This is repeater Program! Limit to 64 chars !!!\n\r");

    //printf("Initial x1: %d, x2: %d\n", x1, x2);
    //swipe(&x1, &x2);
    //printf("Next x1: %d, x2: %d\n", x1, x2);
    
    //char* externalString = getTextToDisplay();
    //printf(externalString);
    char num = (char)fgetc(stdin);
    char str[2];
    str[0] = num;
    str[1] = '\0';
    printf("You input the char: ");
    printf(str);
    printf("\n");
    fgetc(stdin);

    //FILE f;
    FILE* fp;
    // here is important that we fetch pointer to pointer by &
    // FILE** fp2 = &fp;
    int success = fopen_s(&fp, "test.txt", "w+");
    if (success != 0 || fp == NULL) {
        printf("Null pointer to file");
        return -1;
    }
    // this is wide char encoding so this is UTF-16 encoding
    const char* testString = L"������";
    fwprintf(fp, testString);
    fclose(fp);

    success = fopen_s(&fp, "test.txt", "rb");
    if (success != 0 || fp == NULL) {
        printf("Null pointer to file");
        return -1;
    }
    printf("Written to file the string: %s\r\n", testString);
    int val;
    char cont[2];
    cont[1] = '\0';
    /*while ((val = fgetc(fp)) != EOF)
    {
        printf("%d ", val);
        cont[0] = (char)val;
        printf(&cont);
        printf(" ");
    }
    printf("\n");*/

    int readItemsCount;
    // it is not good to use just 127 char as int based on 8 bits
    // for unicode as utf-8 better to use unsigned int as 32 bits
    // use unsgigned char to have 8 bits
    unsigned char arr[2];
    arr[1] = '\0';
    printf("This is output from file\r\n");
    while ((readItemsCount = fread(arr, sizeof(unsigned char), 1, fp)) != 0)
    {
        //printf("%d ", arr[0]);
        //printByteIntAsBites(arr[0]);
        printByteIntAsHex((int)arr[0], "hex");
    }
    printf("\r\n");

    return 0;
} 

int swipe(int *val1, int *val2)
{
    int saved = *val1;
    *val1 = *val2;
    *val2 = saved;
}

char* stringRev(char* src)
{
    const int len = strlen(src);
    char * newStr = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = len - 1; i >= 0; i--)
    {
        *(newStr + (len - 1 - i)) = *(src + i);
    }
    *(newStr + len) = '\0';
    return newStr;
}

void printByteIntAsBites(unsigned char number)
{
    /*for (int i = 0; i < 8; i++)
    {
        unsigned char mask = 1 << i;
        printf(number & mask ? "1" : "0");
    }*/
    int i = 7;
    int mask = 1;
    while (i >= 0)
    {
        printf(number & mask ? "1" : "0");
        i--;
        mask = mask << 1;
    }
    printf("\r\n");
}


void printByteIntAsHex(int number, char * base)
{
    const char* hexSpace = "0123456789ABCDEF";
    
    // each pointer has "address"
    char *result = "";
    switch (*base)
    {
        default:
            convertToDiffBase(number, 16, &result, hexSpace);
    }
    char * resultFinal = stringRev(result);
    free(result);
    printf(resultFinal);
    printf("\r\n");
    
    // if we divide by 16 then only lefts what is less than 16 so this is 0 order
    // what is integer part if it is greater than 16 divide it once again and what lefts is 1 order and the integer part
    // should be divided once again by 16 and repeat it

}






