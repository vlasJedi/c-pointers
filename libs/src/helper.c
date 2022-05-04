//#include <stdio.h>
#include <string.h>
//#include <stdlib.h>
#include <malloc.h>


char* appendToString(char* baseString, char* appendix);

/**
 * @brief Converts number to string with changing base as option
 * 
 * @param number 
 * @param base 
 * @param result 
 * @param space  - this is set of chars to represent the base
 */
void convertToDiffBase(int number, int base, char** result, char* space)
{
    int mainPart = number / base;
    int rest = number % base;
    char appendix[2];
    appendix[0] = *(space + rest);
    appendix[1] = '\0';
    *result = appendToString(*result, appendix);
    if (mainPart == 0) {
        return;
    }
    if (mainPart < base) {
        appendix[0] = *(space + mainPart);
        *result = appendToString(*result, appendix);
        return;
    }
    convertToDiffBase(mainPart, base, result, space);
};

/**
 * @brief Appends strings and return new alloc pointer to it
 * 
 * @param baseString 
 * @param appendix 
 * @return char* 
 */
char* appendToString(char* baseString, char* appendix)
{
    char* destStr = (char*) malloc(sizeof(char) * (strlen(baseString) + strlen(appendix) + 1));
    strcpy(destStr, baseString);
    // strcat requires that dest already has allocated space
    strcat(destStr, appendix);
    return destStr;
}