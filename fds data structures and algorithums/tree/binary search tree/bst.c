#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

BST* CreateBST(){
    BST* bst = (BST*)malloc(sizeof(BST));
    Node* root = bst->root = NULL;
    bst->size = 0;
    return bst;
}

static CreateNode(int val){
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = val;
    node->left = node->right = NULL;
    return node;
}

static int FindMin(Node* root){
    if(root == NULL){
        return -1; //树为空，返回-1表示未找到
    }
    Node* cur = root;
    while(cur->left != NULL){
        cur = cur->left;
    }
    return cur->key;
}

static int FindMax(Node* root){
    if(root == NULL){
        return -1; //树为空，返回-1表示未找到
    }
    Node* cur = root;
    while(cur->right != NULL){
        cur = cur->right;
    }
    return cur->key;
}

void Insert(Node* root, int val){
    if(root == NULL){
        Node* node = CreateNode(val);
        root = node;
        return;
    }
    else if(val < root->key){
        Insert(root->left, val);
    }else if(val > root->key){
        Insert(root->right, val);
    }else{
        //值已存在，不插入
        return;
    }
}

Node* Search(Node* root ,int key){
    if(root == NULL){
        return NULL;
    }
    if(key < root->key){
        return Search(root->left, key);
    }else if(key > root->key){
        return Search(root->right, key);
    }else{
        return root;
    }
}

void Delete(Node* root, int val){
    if(root == NULL){
        return;
    }
    if(val < root->key){
        Delete(root->left, val);
    }else if(val > root->key){
        Delete(root->right, val);
    }else{
        if(root->left == NULL && root->right == NULL){
            //情况1：无子节点，直接删除
            free(root);
            root = NULL;
        }else if(root->left == NULL){
            //情况2：只有右子节点，替换为右子节点
            Node* tmp = root;
            root = root->right;
            free(tmp);
        }else if(root->right == NULL){
            //情况3：只有左子节点，替换为左子节点   
            Node* tmp = root;
            root = root->left;
            free(tmp);
        }else{
            //情况4：有两个子节点，找到左子树的最大节点替换当前节点
            int left_max = FindMax(root->left);
            root->key = left_max;
            Delete(root->left, left_max);
        }
    }
}

void PreOrderTraversal(Node* root){
    if(root == NULL){
        return;
    }
    printf("%d ", root->key);
    PreOrderTraversal(root->left);
    PreOrderTraversal(root->right);
}

void InOrderTraversal(Node* root){
    if(root == NULL){
        return;
    }
    InOrderTraversal(root->left);
    printf("%d ", root->key);
    InOrderTraversal(root->right);
}

void PostOrderTraversal(Node* root){
    if(root == NULL){
        return;
    }
    PostOrderTraversal(root->left);
    PostOrderTraversal(root->right);
    printf("%d ", root->key);
}

void Clear(Node* root){
    if(root == NULL){
        return;
    }
    Clear(root->left);
    Clear(root->right);
    free(root);
}

void DestroyBST(BST* bst){
    if(bst == NULL){
        return;
    }
    Clear(bst->root);
    free(bst);
}