/*
 * Complete Binary Tree
 * A complete binary tree is a binary tree in which every level,
   except possibly the last, is completely filled, 
   and all nodes are as far left as possible. 
   This property allows us to represent a complete binary tree using an array, 
   where the parent-child relationships can be easily determined by index calculations.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

typedef struct Node{
    int key;
    int left;
    int right;
}Node;

typedef struct CBT{
    Node nodes[MAXN];
    int size;
}CBT;

CBT* tree_create(int n){
    CBT* tree = (CBT*)malloc(sizeof(CBT));
    tree->size = n;
    for(int i = 0; i < n; i++){
        scanf("%d", &tree->nodes[i].key);
        tree->nodes[i].left = (2*i + 1 < n) ? (2*i + 1) : -1;
        tree->nodes[i].right = (2*i + 2 < n) ? (2*i + 2) : -1;
    }
    return tree;
}

void tree_destroy(CBT* tree){
    if(tree == NULL) return;
    free(tree);
}
