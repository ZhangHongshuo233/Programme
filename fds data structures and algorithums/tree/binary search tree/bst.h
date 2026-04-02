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
    Key key;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct BST{
    Node* root;
    int size; 
}BST;

void CreateBST(BST* bst);
Node* SearchBST(BST* bst, Key key);
Node* FindMin(BST* bst);
Node* FindMax(BST* bst);
int Insert(BST* bst, Key key);
int Delete(BST* bst, Key key); 
void PreOrderTraversal(Node* node);
void InOrderTraversal(Node* node);
void DestroyBST(BST* bst);


#endif // BINARY_SEARCH_TREE_H