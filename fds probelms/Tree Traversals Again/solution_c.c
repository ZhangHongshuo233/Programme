/*因为用栈实现二叉树的中序遍历过程中，每一个TreeNode遍历了两次，
第一次push的过程恰好是先序遍历的过程，第二次pop的过程恰好是中序遍历的过程。
因此本题等价于根据先序遍历和中序遍历重建二叉树。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode{
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

//Tree operations
TreeNode* buildTreeFromPreIn(char* preorder, char* inorder, int len){
    if(len <= 0) return NULL;
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = preorder[0];
    root->left = root->right = NULL;
    int pos = 0;
    while(pos < len && inorder[pos] != preorder[0]){
        pos++;
    }
    root->left = buildTreeFromPreIn(preorder + 1, inorder, pos);
    root->right = buildTreeFromPreIn(preorder + 1 + pos, inorder + pos + 1, len - pos - 1);
    return root;
}

void DestroyTree(TreeNode* tree){
    if(tree == NULL){
        return;
    }
    DestroyTree(tree->left);
    DestroyTree(tree->right);
    free(tree);
    tree = NULL;
}

static int cnt = 0;
void PostOrderTraversal(TreeNode* tree, int n){
    if(tree == NULL){
        return;
    }
    cnt++;
    PostOrderTraversal(tree->left, n);
    PostOrderTraversal(tree->right, n);
    printf("%c", tree->data);
    if(cnt < n){
        printf(" ");
    }
}

typedef struct StackNode{
    TreeNode *node;
    struct StackNode *next;
}StackNode;

typedef struct LinkStack{
    StackNode *top;
    int size;
}LinkStack;

// Stack operations
LinkStack* CreateStack(){
    LinkStack *stack = (LinkStack*)malloc(sizeof(LinkStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void Push(LinkStack* stack, TreeNode* node){
    StackNode* NewNode = (StackNode*)malloc(sizeof(StackNode));
    NewNode->node = node;
    NewNode->next = stack->top;
    stack->top = NewNode;
    stack->size++;
}

int IsEmpty(LinkStack* stack){
    return stack->size == 0;
}

void Pop(LinkStack* stack){
    if(IsEmpty(stack)) return;
    StackNode* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    stack->size--;
}

TreeNode* GetTop(LinkStack* stack){
    if(IsEmpty(stack)) return NULL;
    return stack->top->node;
}

void DestroyStack(LinkStack* stack){
    while(!IsEmpty(stack)){
        Pop(stack);
    }
    free(stack);
}


int main(){
    char preorder[31], inorder[31];
    int preidx = 0, inidx = 0;
    char* str = (char*)malloc(10*sizeof(char));
    int n;
    scanf("%d", &n);
    LinkStack* stack = CreateStack();
    for(int i=0;i<2*n;i++){
        scanf("%s",str);
        if(strcmp(str,"Push") == 0){
            char ch;
            scanf(" %c", &ch);
            TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
            node->data = ch;
            Push(stack, node);
            preorder[preidx++] = ch;
        }
        else if(strcmp(str,"Pop") == 0){
            TreeNode* node = GetTop(stack);
            Pop(stack);
            inorder[inidx++] = node->data;
        }
    }
    DestroyStack(stack);
    preorder[preidx] = '\0';
    inorder[inidx] = '\0';
    TreeNode* root = buildTreeFromPreIn(preorder, inorder, n);
    PostOrderTraversal(root, n);
    DestroyTree(root);
    return 0;
}