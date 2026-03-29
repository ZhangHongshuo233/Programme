#include <stdio.h>
#include "tree/tree.h"

// tree.c 中已实现，但 tree.h 当前未声明的接口
void CreateTree(TreeNode **root, char *data, int *idx);
void LevelOrderTraversal(TreeNode *tree);

int main(void)
{
    TreeNode *root = NULL;
    // 前序序列，# 表示空结点
    char data[] = "abd##e##c#fh###";
    int idx = 0;

    // 创建二叉树
    CreateTree(&root, data, &idx);

    printf("===== 递归遍历 =====\n");
    printf("前序遍历: ");
    PreOrderTraversal(root);
    printf("\n中序遍历: ");
    InOrderTraversal(root);
    printf("\n后序遍历: ");
    PostOrderTraversal(root);

    printf("\n===== 非递归遍历 =====\n");
    printf("前序遍历: ");
    PreOrderTraversalNonRecursive(root);
    printf("\n中序遍历: ");
    InOrderTraversalNonRecursive(root);
    printf("\n后序遍历: ");
    PostOrderTraversalNonRecursive(root);

    printf("\n===== 层序遍历 =====\n");
    printf("层序遍历: ");
    LevelOrderTraversal(root);
    printf("\n");

    DestroyTree(root);
    return 0;
}
