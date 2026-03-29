#ifndef _NODE_H_
#define _NODE_H

typedef struct _node{
    int value;
    struct _node* next; 
} Node;

void add(List* List_ref,int number);
void print(List* List_ref);
void delete(List* List_ref,int number);
void freeList(List* List_ref);

#endif 