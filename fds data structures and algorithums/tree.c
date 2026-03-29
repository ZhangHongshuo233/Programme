#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "linkstack_for_tree.h"

void CreateTree(TreeNode** root, char* data, int* idx) {
    char ch = data[(*idx)++];
    //空结点，直接返回
    if(ch == '#'){
        *root = NULL;
        return;
    }else{
        //分配结点内存
        *root = (TreeNode*)malloc(sizeof(TreeNode));
        if(*root == NULL){
            printf("Memory allocation failed!\n");
            return;
        }
        //存入当前结点数据
        (*root)->data = ch;
        //递归创建左子树
        CreateTree(&((*root)->left), data, idx);
        //递归创建右子树
        CreateTree(&((*root)->right), data, idx);
    }
}

