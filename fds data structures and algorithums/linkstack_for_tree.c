#include "linstack_for_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkStack* CreateLinkStack(){
    LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
    if(stack == NULL){
        printf("Memory allocation failed!\n");
        return NULL;
    }
    stack->top = NULL;
    stack->count = 0;
    return stack;
}
int Push(LinkStack* stack, StackNode* node){
    if(stack == NULL || node == NULL){
        printf("Stack or node is NULL!\n");
        return -1;
    }
    node->next = stack->top;
    stack->top = node;
    stack->count++;
    return 0;
}
TreeNode* Pop(LinkStack* stack, char* data){
    if(stack == NULL || data == NULL){
        printf("Stack or data is NULL!\n");
        return NULL;
    }
    if(stack->top == NULL){
        printf("Stack is empty!\n");
        return NULL;
    }
    StackNode* node = stack->top;
    stack->top = stack->top->next;
    stack->count--;
    *data = node->tree_node->data;
    free(node);
    return node->tree_node;
}
int IsEmpty(LinkStack* stack){
    if(stack == NULL){
        printf("Stack is NULL!\n");
        return -1;
    }
    return stack->top == NULL;
}
int ClearStack(LinkStack* stack){
    if(stack == NULL){
        printf("Stack is NULL!\n");
        return -1;
    }
    while(stack->top != NULL){
        StackNode* node = stack->top;
        stack->top = stack->top->next;
        free(node);
    }
    stack->count = 0;
    return 0;
}
void DestroyStack(LinkStack* stack){
    ClearStack(stack);
    free(stack);
}
