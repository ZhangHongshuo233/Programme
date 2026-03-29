#ifndef _LINSTACK_FOR_TREE_H_
#define _LINSTACK_FOR_TREE_H_

typedef struct TreeNode{
    char data;
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
    int size;
}LinkStack;

//栈操作函数声明
LinkStack* CreateLinkStack();
int PushStack(LinkStack* stack, TreeNode* node);
TreeNode* PopStack(LinkStack* stack);
int IsEmptyStack(LinkStack* stack);
int ClearStack(LinkStack* stack);
void DestroyStack(LinkStack* stack);

#endif // _LINSTACK_FOR_TREE_H_