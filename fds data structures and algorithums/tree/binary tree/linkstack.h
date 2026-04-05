#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

#include "binary tree.h"

// stack node for tree traversal
typedef struct stacknode {
    TreeNode* tree_node;
    struct stacknode* next;
} StackNode;

// linked stack for tree traversal
typedef struct {
    StackNode* top;
    int size;
} LinkStack;

// stack operation declarations
LinkStack* CreateLinkStack();
int PushStack(LinkStack* stack, TreeNode* node);
TreeNode* PopStack(LinkStack* stack);
int IsEmptyStack(LinkStack* stack);
void DestroyLinkStack(LinkStack* stack);

#endif // _LINKSTACK_H_
