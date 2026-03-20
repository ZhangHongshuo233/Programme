#ifndef _TREE_H_
#define _TREE_H_

typedef struct data{
    int val;
    char name[20];
}data;

typedef struct node{
    data data;
    struct node *left;
    struct node *right;
}node;

//stack for tree traversal(栈结点，用于非递归遍历树)
typedef struct stacknode{
    node* tree_node;
    struct stacknode *next;
}stacknode;

typedef struct tree{
    node *top;
    int size;
}tree;

  


#endif 