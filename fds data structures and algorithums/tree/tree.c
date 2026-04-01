#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "linkstack.h"
#include "linkque.h"

//创建树(Create Tree)
void CreateRoot(TreeNode** root, char* data, int* idx) {
    //示例：abd##e##c#fh###
//         a
//       /   \
//      b     c
//     / \     \
//    d   e     f
//             /
//            h
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
        CreateRoot(&((*root)->left), data, idx);
        //递归创建右子树
        CreateRoot(&((*root)->right), data, idx);
    }
}


//深度优先遍历(DFS,Depth-First Search)的递归实现：

//1.前序遍历(PreOrder Traversal)
void PreOrderTraversal(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    //访问根结点
    printf("%c ", tree->data);
    //遍历左子树
    PreOrderTraversal(tree->left);
    //遍历右子树
    PreOrderTraversal(tree->right);

    //理论上输出应该是：a b d e c f h
}

//2.中序遍历(InOrder Traversal)
void InOrderTraversal(TreeNode* tree){
    if(tree == NULL){
        return;
    }

    //遍历左子树
    InOrderTraversal(tree->left);
    //访问根结点
    printf("%c ", tree->data);
    //遍历右子树
    InOrderTraversal(tree->right);

    //理论上输出应该是：d b e a f h c
}

//3.后序遍历(PostOrder Traversal)
void PostOrderTraversal(TreeNode* tree){
    if(tree == NULL){
        return ;
    }
    //遍历左子树
    PostOrderTraversal(tree->left);
    //遍历右子树
    PostOrderTraversal(tree->right);
    //访问根结点
    printf("%c ", tree->data);

    //理论上输出应该是：d e b h f c a   
}

//深度优先遍历(DFS,Depth-First Search)的非递归实现：

//1.前序遍历(PreOrder Traversal)
//核心思路：
//  1.根结点入栈，循环弹出栈顶结点并访问（符合 “根优先” 的前序规则）；
//  2.先将右子结点入栈（栈先进后出，保证左子树先遍历），再将左子结点入栈；
//  3.重复直到栈为空。

void PreOrderTraversalNonRecursive(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    LinkStack* stack = CreateLinkStack();
    PushStack(stack, tree);
    while(!IsEmptyStack(stack)){
        //弹出栈顶结点
        TreeNode* node = PopStack(stack);
        //访问当前结点
        printf("%c ", node ->data);
        //先将右子结点入栈
        if(node->right != NULL){
            PushStack(stack, node->right);
        }
        //再将左子结点入栈
        if(node->left != NULL){
            PushStack(stack, node->left);
        }
    }
    DestroyLinkStack(stack);
}

//2.中序遍历(InOrder Traversal)
//核心思路：
//  1.从根结点开始，将所有左子结点入栈，直到左子结点为空（符合 “先左” 的中序规则）；
//  2.弹出栈顶结点并访问，然后处理其右子树；
//  3.重复直到栈为空且当前结点为 NULL。

void InOrderTraversalNonRecursive(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    LinkStack* stack = CreateLinkStack();
    TreeNode* cur = tree;
    while(!IsEmptyStack(stack) || cur != NULL){
        //左子结点全部入栈 
        while(cur != NULL){
            PushStack(stack, cur);
            cur = cur->left;
        }
        //弹出栈顶结点并访问
        cur = PopStack(stack);
        printf("%c ", cur->data);
        //处理右子树
        cur = cur->right; 
    }
    DestroyLinkStack(stack);
}

//3.后序遍历(PostOrder Traversal)
//核心思路：
// 栈 1 存储待处理结点，栈 2 存储访问顺序；
// 根结点入栈 1，弹出后入栈 2，再将左、右子结点依次入栈 1；
// 栈 1 为空时，依次弹出栈 2 结点并访问（栈 2 顺序为根 - 右 - 左，弹出后为左 - 右 - 根，符合后序规则）。

void PostOrderTraversalNonRecursive(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    LinkStack* stack1 = CreateLinkStack();
    LinkStack* stack2 = CreateLinkStack();
    PushStack(stack1, tree);
    while(!IsEmptyStack(stack1)){
        TreeNode* node = PopStack(stack1);
        PushStack(stack2, node);
        //左子结点先入栈1
        if(node->left != NULL){
            PushStack(stack1, node->left);
        }
        //右子结点后入栈1
        if(node->right != NULL){
            PushStack(stack1, node->right);
        }
    }
    //遍历栈2，输出后序结果
    while(!IsEmptyStack(stack2)){
        TreeNode* node = PopStack(stack2);
        printf("%c ", node->data);
    }
    DestroyLinkStack(stack1);
    DestroyLinkStack(stack2);
}

/*
正确性证明
1. 栈 stack2 中的节点顺序
考虑节点压入 stack2 的顺序。由于 stack1 是栈（后进先出），在每一步中：
• 当前节点 cur 被压入 stack2。
• 随后将 cur 的左、右孩子按先左后右的顺序压入 stack1。
由于后压入的右孩子位于 stack1 的栈顶，因此下一次循环将先处理右孩子，后处理左孩子。这意味着：
• 在 stack1 中，右子树的所有节点将先于左子树的节点被弹出并压入 stack2。
• 因此，压入 stack2 的顺序是：根节点 → 右子树的所有节点（按相同规则）→ 左子树的所有节点。
这种顺序恰好是先序遍历的镜像，即“根-右-左”的遍历顺序。
2. 逆序输出得到后序
后序遍历的顺序是“左-右-根”。将“根-右-左”序列逆序，即得到“左-右-根”序列：
• 逆序后，原本在序列末尾的“左子树”节点变为开头，原本在开头的“根”变为末尾，且“右子树”节点位于中间，正好符合后序要求。
由于 stack2 是栈，其弹出顺序恰好是压入顺序的逆序。因此，从 stack2 中依次弹出并打印，即输出“左-右-根”的后序遍历序列。
3. 递归结构的保持
该算法对每个子树都采用相同的处理方式：
• 对于任意节点，其左右子树被分别处理，且右子树先于左子树被压入 stack2。
• 这保证了在 stack2 中，每个子树的节点都被集中放置，且顺序符合“根-右-左”的递归定义。
因此，通过数学归纳法可知，对于任意二叉树，该算法均能正确输出后序遍历序列。
*/

//3.2 后序遍历的第二种非递归实现（单栈 + pre 指针）
//核心思路：
//  1.将所有左子结点入栈；
//  2.查看栈顶结点（不弹出）：
//    若右子结点存在且尚未被访问（right != pre），则转向右子树；
//    否则访问当前结点，将 pre 更新为该结点，并将 cur 置为 NULL
//    以防止循环重新入栈。

void PostOrderTraversalNonRecursive2(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    LinkStack* stack = CreateLinkStack();
    TreeNode* cur = tree;
    TreeNode* pre = NULL; //记录上一个访问的结点
    while(!IsEmptyStack(stack) || cur != NULL){
        while(cur != NULL){
            PushStack(stack, cur);
            cur = cur->left;
        }
        //查看栈顶结点但不弹出
        cur = stack->top->tree_node;
        //如果右子结点存在且未被访问过，则处理右子树
        if(cur->right != NULL && cur->right != pre){
            cur = cur->right;
        }
        //否则访问当前结点
        else{
            printf("%c ", cur->data);
            pre = PopStack(stack);
            cur = NULL; //重置cur，避免重复入栈
        }
    }
    DestroyLinkStack(stack);
}

// 广度优先遍历(BFS,Breadth-First Search)：层序遍历（队列实现）
/* 
    层序遍历的顺序是从上到下、从左到右访问每一层的结点，
    其实现依赖队列的 “先进先出” 特性，
    与深度优先遍历的前序、中序、后序规则完全不同。
*/
//核心思路：
// 1.根结点入队，循环出队访问当前结点；
// 2.访问当前结点后，将其左、右子结点依次入队；
// 3.重复直到队列为空。

void LevelOrderTraversal(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    //创建空队列
    LinkQueue* queue = CreateLinkQueue();
    //根结点入队
    EnterLinkQueue(queue, tree);
    while(!IsEmptyLinkQueue(queue)){
        //出队访问当前结点
        TreeNode* node = *(GetHeadLinkQueue(queue));
        printf("%c ", node->data);
        //左子结点入队
        if(node->left != NULL){
            EnterLinkQueue(queue, node->left);
        }
        //右子结点入队
        if(node->right != NULL){
            EnterLinkQueue(queue, node->right);
        }
        //队首结点出队
        QuitLinkQueue(queue);   
    }
    DestroyLinkQueue(queue);
}

void DestroyTree(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    //递归销毁左子树
    DestroyTree(tree->left);
    //递归销毁右子树
    DestroyTree(tree->right);
    //释放当前结点
    free(tree);
    tree = NULL;
}