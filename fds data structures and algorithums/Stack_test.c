#include "linkstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    LinkStack* stack = CreateLinkStack();
    if (stack == NULL) {
        printf("Failed to create stack.\n");
        return 1;
    }

    datatype data1 = {1, "First"};
    datatype data2 = {2, "Second"};
    datatype data3 = {3, "Third"};

    push(stack, &data1);
    push(stack, &data2);
    push(stack, &data3);

    printf("Stack size: %d\n", GetSize(stack));

    datatype topData;
    if (getTop(stack) != NULL) {
        printf("Top element: id=%d, name=%s\n", getTop(stack)->val, getTop(stack)->name);
    }

    while (!IsEmpty(stack)) {
        if (pop(stack, &topData) == 0) {
            printf("Popped element: id=%d, name=%s\n", topData.val, topData.name);
        }
    }

    printf("Stack size after popping all elements: %d\n", GetSize(stack));
    clearStack(stack);
    free(stack);
    return 0;
}

//运行时在cmd中输入：gcc Stack_test.c linkstack.c -o stack_test.exe
//输入.\stack_test.exe运行程序