#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode{
    char data;
    struct TreeNode* left;
    struct TreeNode* right;
}TreeNode;

//(1)根据前序和中序遍历重建二叉树
// 输入：前序序列、中序序列、序列长度
// 输出：重建后的二叉树根节点
TreeNode* bulidTreeFromRreIn(char* preorder, char* inorder, int len){
    if(len <= 0){
        return NULL;
    }
    //1.创建根结点
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = preorder[0];
    root->left = root->right = NULL;

    //2.在中序序列中找到根结点的位置
    int pos = 0;
    while(pos < len && inorder[pos] != root->data){
        pos++;
    }

    //3.递归构建左子树和右子树
    //左子树：前序从1开始，长度pos；中序从头开始，长度pos
    root->left = bulidTreeFromRreIn(preorder + 1, inorder, pos);
    //右子树：前序从1+pos开始，长度len-pos-1；中序从pos+1开始，长度len-pos-1
    root->right = bulidTreeFromRreIn(preorder + 1 + pos, inorder + pos + 1, len - pos - 1);
    return root;
}

//(2)根据中序和后序遍历重建二叉树
// 输入：中序序列、后序序列、序列长度
// 输出：重建后的二叉树根节点
TreeNode* bulidTreeFromInPost(char* inorder, char* postorder, int len){
    //递归终止条件：序列长度为0(空树)
    if(len <= 0){
        return NULL;
    }
    //1.创建根结点(后序遍历的最后一个元素是根结点)
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = postorder[len - 1];
    root->left = root->right = NULL;

    //2.在中序序列中找到根结点的位置
    int pos = 0;
    while(pos < len && inorder[pos] != root->data){
        pos++;
    }

    //3.递归构建左子树和右子树
    //左子树：中序从头开始，长度pos；后序从头开始，长度pos
    root->left = bulidTreeFromInPost(inorder, postorder, pos);
    //右子树：中序从pos+1开始，长度len-pos-1；后序从pos开始，长度len-pos-1
    root->right = bulidTreeFromInPost(inorder + pos + 1, postorder + pos, len - pos -1);

    return root;
}

// 前序遍历：根 → 左 → 右
void preorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    printf("%c ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// 中序遍历：左 → 根 → 右
void inorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    printf("%c ", root->data);
    inorderTraversal(root->right);
}

// 后序遍历：左 → 右 → 根
void postorderTraversal(TreeNode* root) {
    if (root == NULL) return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%c ", root->data);
}

// 递归释放二叉树内存，避免内存泄漏
void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);   // 释放左子树
    freeTree(root->right);  // 释放右子树
    free(root);             // 释放当前节点
}
