/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_LINE_LENGTH 256

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char* endptr;
    errno = 0;
    long n = strtol(argv[1], &endptr, 10);

    if (errno != 0 || *endptr != '\0' || n <= 0) {
        printf("Invalid value for <n>: %s\n", argv[1]);
        return 1;
    }

    char** circularBuffer = (char**)malloc(sizeof(char*) * n);
    for (long i = 0; i < n; i++) {
        circularBuffer[i] = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
    }

    long index = 0;
    char line[MAX_LINE_LENGTH];

    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        strcpy(circularBuffer[index], line);
        index = (index + 1) % n;
    }

    printf("Last %ld lines:\n", n);
    for (long i = 0; i < n; i++) {
        printf("%s", circularBuffer[index]);
        index = (index + 1) % n;
    }

    for (long i = 0; i < n; i++) {
        free(circularBuffer[i]);
    }
    free(circularBuffer);

    return 0;
}