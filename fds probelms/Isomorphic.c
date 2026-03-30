typedef char ElementType;
typedef struct TreeNode *Tree;
struct TreeNode {
    ElementType Element;
    Tree  Left;
    Tree  Right;
};
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Isomorphic( Tree T1, Tree T2 ){
    if(T1 == NULL && T2 == NULL){
        return 1;
    }else if (T1 == NULL || T2 == NULL){
        return 0;
    }else if (T1->Element != T2->Element){
        return 0;
    }
    return (Isomorphic(T1->Left, T2->Left) && Isomorphic(T1->Right, T2->Right)) ||
           (Isomorphic(T1->Left, T2->Right) && Isomorphic(T1->Right, T2->Left));
}