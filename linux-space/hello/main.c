#include <stdio.h>

// int count and array of pointers to strings
int main(int argc, char* argv[]) {
    char buffer[20];
    int index = 0;
    while(1) {
        if ((buffer[index] = (char) fgetc(stdin)) == '\n'
           || (index + 1) == sizeof(buffer)) {
            buffer[index] = 0;
            printf("%s\n", buffer);
            index = 0;
        } else {
            index++;
        }
    }
    printf("Encountered new line, exiting...\n");
    return 0;
}