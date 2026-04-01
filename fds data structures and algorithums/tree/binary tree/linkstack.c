#include "linkstack.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// 创建空栈
LinkStack* CreateLinkStack()
{
    LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
    if (NULL == stack)
    {
        printf("CreateLinkStack malloc error\n");
        return NULL;
    }
    stack->top = NULL;
    stack->size = 0;
    return stack;
}
 
// 入栈操作
int PushStack(LinkStack* stack, TreeNode* node)
{
    if (NULL == stack || NULL == node)
    {
        return 1;
    }
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (NULL == newNode)
    {
        printf("PushStack malloc error\n");
        return 1;
    }
    newNode->tree_node = node;
    newNode->next = stack->top;
    stack->top = newNode;
    stack->size++;
    return 0;
}
 
// 出栈操作
TreeNode* PopStack(LinkStack* stack)
{
    if (NULL == stack || IsEmptyStack(stack))
    {
        return NULL;
    }
    StackNode* tmp = stack->top;
    TreeNode* TreeNode = tmp->tree_node;
    stack->top = tmp->next;
    free(tmp);
    stack->size--;
    return TreeNode;
}
 
// 判断栈是否为空
int IsEmptyStack(LinkStack *stack)
{
    return (stack == NULL || stack->size == 0);
}
 
// 销毁栈
void DestroyLinkStack(LinkStack *stack)
{
    if (NULL == stack)
    {
        return;
    }
    while (!IsEmptyStack(stack))
    {
        PopStack(stack);
    }
    free(stack);
}