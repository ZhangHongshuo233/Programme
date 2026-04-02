#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum KeyType{
    KEY_INT,
    KEY_CHAR
}KeyType;

typedef struct key{
    KeyType type;
    union{
        int intValue;
        char charValue;
    }value;
}Key;

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct BST{
    Node* root;
    int size; 
}BST;

BST* CreateBST();  
Node* Search(Node* root, int val);
int  FindMin(Node* root);
int  FindMax(Node* root);
void Insert(Node* root, int val);
void Delete(Node* root, int val); 
void PreOrderTraversal(Node* root);
void InOrderTraversal(Node* root);
void PostOrderTraversal(Node* root);
void DestroyBST(BST* bst);


#endif // BINARY_SEARCH_TREE_H