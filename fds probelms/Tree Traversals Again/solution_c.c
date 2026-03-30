/*
本题中，非递归中序遍历的 Push 序列等价于先序遍历，
Pop 序列等价于中序遍历。
因此可先恢复先序和中序，再重建二叉树并输出后序。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

static TreeNode *BuildTreeFromPreIn(
    const int *preorder,
    const int *inorder,
    int preL,
    int preR,
    int inL,
    int inR)
{
    if (preL > preR) {
        return NULL;
    }

    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    if (root == NULL) {
        return NULL;
    }

    int rootVal = preorder[preL];
    root->data = rootVal;
    root->left = NULL;
    root->right = NULL;

    int k = inL;
    while (k <= inR && inorder[k] != rootVal) {
        k++;
    }

    int leftSize = k - inL;
    root->left = BuildTreeFromPreIn(preorder, inorder, preL + 1, preL + leftSize, inL, k - 1);
    root->right = BuildTreeFromPreIn(preorder, inorder, preL + leftSize + 1, preR, k + 1, inR);
    return root;
}

static void PostOrderTraversal(TreeNode *root, int *isFirst)
{
    if (root == NULL) {
        return;
    }

    PostOrderTraversal(root->left, isFirst);
    PostOrderTraversal(root->right, isFirst);

    if (!(*isFirst)) {
        printf(" ");
    }
    printf("%d", root->data);
    *isFirst = 0;
}

static void DestroyTree(TreeNode *root)
{
    if (root == NULL) {
        return;
    }
    DestroyTree(root->left);
    DestroyTree(root->right);
    free(root);
}

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }

    int preorder[31];
    int inorder[31];
    int preIdx = 0;
    int inIdx = 0;

    int stack[31];
    int top = -1;
    char op[8];

    for (int i = 0; i < 2 * n; i++) {
        if (scanf("%7s", op) != 1) {
            return 0;
        }

        if (strcmp(op, "Push") == 0) {
            int x;
            scanf("%d", &x);
            preorder[preIdx++] = x;
            stack[++top] = x;
        } else {
            inorder[inIdx++] = stack[top--];
        }
    }

    TreeNode *root = BuildTreeFromPreIn(preorder, inorder, 0, n - 1, 0, n - 1);
    int isFirst = 1;
    PostOrderTraversal(root, &isFirst);
    printf("\n");

    DestroyTree(root);
    return 0;
}