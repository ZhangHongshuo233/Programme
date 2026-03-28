#include "linkstack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkStack* CreateLinkStack(){
    LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
    if (stack == NULL) {
        return NULL;
    }
    stack->top = NULL;
    stack->count = 0;
    return stack;
}

int Push(LinkStack* stack, datatype* data) {
    if (stack == NULL || data == NULL) {
        printf("Push failed: invalid parameter.\n");
        return 1; 
    }

    node* newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Push failed: memory allocation failed.\n");
        return 1; 
    }
    memcpy(&(newNode->data), data, sizeof(datatype));
    newNode->next = stack->top;
    stack->top = newNode;
    stack->count++;
    return 0; // Success
}

int GetSize(LinkStack* stack) {
    return stack?stack->count:0;
}

int IsEmpty(LinkStack* stack) {
    return (stack->count == 0) || (stack->top == NULL);
}

int Pop(LinkStack* stack, datatype* data) {
    if (IsEmpty(stack)) {
        printf("Pop failed: stack is empty.\n");
        return 1; 
    }

    node* temp = stack->top;
    memcpy(data, &(temp->data), sizeof(datatype));
    stack->top = temp->next;
    free(temp);
    stack->count--;
    return 0; // Success
}

datatype* GetTop(LinkStack* stack) {
    if (IsEmpty(stack)) {
        printf("Get top failed: stack is empty.\n");
        return NULL; 
    }
    return &(stack->top->data);
}

int ClearStack(LinkStack* stack) {
    if(stack == NULL){
        return 1;
    }
    node* current = stack->top;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
    stack->count = 0;
    return 0;
}

int DestroyStack(LinkStack* stack) {
    if (stack == NULL) {
        return 1; 
    }
    ClearStack(stack);
    free(stack);
    return 0; 
}