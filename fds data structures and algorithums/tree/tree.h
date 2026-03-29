#ifndef _TREE_H_
#define _TREE_H_

typedef struct TreeNode{
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

//树操作函数声明
void CreateRoot(TreeNode** root, char* data, int* idx);
void PreOrderTraversal(TreeNode* tree);
void InOrderTraversal(TreeNode* tree);
void PostOrderTraversal(TreeNode* tree);
void PreOrderTraversalNonRecursive(TreeNode* tree);
void InOrderTraversalNonRecursive(TreeNode* tree);
void PostOrderTraversalNonRecursive(TreeNode* tree);
void LevelOrderTraversal(TreeNode* tree);
void DestroyTree(TreeNode* tree);
#endif 