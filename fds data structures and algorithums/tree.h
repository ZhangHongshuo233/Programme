#ifndef _TREE_H_
#define _TREE_H_

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
    int count;
}LinkStack;

//栈操作函数声明
LinkStack* CreateLinkStack();
int Push(LinkStack* stack, StackNode* node);
TreeNode* Pop(LinkStack* stack, char* data);
int IsEmpty(LinkStack* stack);
int ClearStack(LinkStack* stack);
void DestroyStack(LinkStack* stack);

//树操作函数声明
void CreateRoot(TreeNode** root, char* data, int* idx);
void PreOrderTraversal(TreeNode* tree);
void InOrderTraversal(TreeNode* tree);
void PostOrderTraversal(TreeNode* tree);
void PreOrderTraversalNonRecursive(TreeNode* tree);
void InOrderTraversalNonRecursive(TreeNode* tree);
void PostOrderTraversalNonRecursive(TreeNode* tree);
int GetTreeDepth(TreeNode* tree);
int GetNodeCount(TreeNode* tree);
int GetLeafCount(TreeNode* tree);
int ClearTree(TreeNode** tree);
void DestroyTree(TreeNode** tree);
#endif 