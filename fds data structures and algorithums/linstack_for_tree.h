#ifndef _LINSTACK_FOR_TREE_H_
#define _LINSTACK_FOR_TREE_H_

typedef struct data{
    int val;
    char name[20];
}datatype;

typedef struct TreeNode{
    datatype data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

//stack for tree traversal(栈结点结构，用于非递归遍历树)
typedef struct stacknode{
    TreeNode* tree_node;
    struct stacknode *next;
}StackNode;

//栈结构(链式栈)
typedef struct{
    StackNode* top;
    int count;
}LinkStack;

//栈操作函数声明
LinkStack* CreateLinkStack();
int Push(LinkStack* stack, StackNode* node);
TreeNode* Pop(LinkStack* stack, datatype* data);
int IsEmpty(LinkStack* stack);
int ClearStack(LinkStack* stack);
void DestroyStack(LinkStack* stack);

#endif // _LINSTACK_FOR_TREE_H_