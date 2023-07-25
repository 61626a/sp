/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

typedef struct Node {
    char line[MAX_LINE_LENGTH];
    struct Node* next;
} Node;

Node* createNode(const char* line) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        strncpy(newNode->line, line, MAX_LINE_LENGTH - 1);
        newNode->line[MAX_LINE_LENGTH - 1] = '\0'; // Ensure null-termination
        newNode->next = NULL;
    }
    return newNode;
}

void freeList(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }

    char* endptr;
    long n = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || n <= 0) {
        printf("Invalid value for <n>: %s\n", argv[1]);
        return 1;
    }

    Node* head = NULL;
    Node* tail = NULL;

    char line[MAX_LINE_LENGTH];
    long lineCount = 0;

    while (fgets(line, MAX_LINE_LENGTH, stdin) != NULL) {
        Node* newNode = createNode(line);
        if (newNode == NULL) {
            printf("Memory allocation failed.\n");
            freeList(head);
            return 1;
        }

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }

        lineCount++;

        if (lineCount > n) {
            Node* temp = head;
            head = head->next;
            free(temp);
        }
    }

    printf("Last %ld lines:\n", n);
    Node* current = head;
    while (current != NULL) {
        printf("%s", current->line);
        current = current->next;
    }

    freeList(head);

    return 0;
}
