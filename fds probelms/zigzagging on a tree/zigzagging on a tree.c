#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

//Tree operations
TreeNode* bulidTreeFromInPost(int* inorder, int* postorder,
int len){
    if(len <= 0) return NULL;

    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->val = postorder[len-1];
    root->left = root->right = NULL;

    int pos = 0;
    while(pos < len && inorder[pos] != root->val) pos++;
    root->left = bulidTreeFromInPost(inorder, postorder, pos);
    root->right = bulidTreeFromInPost(inorder + pos + 1, postorder + pos, len - pos - 1);
    return root;
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

// Zigzag Level Order Traversal
void ZigzagLevelOrder(TreeNode* tree, int n){
    if(tree == NULL) return;
    LinkStack* stack1 = CreateStack();
    LinkStack* stack2 = CreateStack();
    Push(stack1, tree);
    int flag = 0;
    int cnt = 0;
    while(!IsEmpty(stack1)){
        TreeNode* node = GetTop(stack1);
        printf("%d", node->val);
        cnt++;
        if(cnt < n) printf(" ");

        Pop(stack1);
        if(flag){
            if(node->left){
                Push(stack2, node->left);
            }
            if(node->right){
                Push(stack2, node->right);
            }
        }else{
            if(node->right){
                Push(stack2, node->right);
            }   
            if(node->left){
                Push(stack2, node->left);
            }
        }
        if(IsEmpty(stack1)){
            LinkStack* temp = stack1;
            stack1 = stack2;
            stack2 = temp;
            flag = !flag;
        }
    }
    free(stack1);
    free(stack2);

}


int main(){
    int n;
    scanf("%d", &n);
    int inorder[n], postorder[n];
    for(int i=0; i<n; i++){
        scanf("%d", &inorder[i]);
    }
    for(int i=0; i<n; i++){
        scanf("%d", &postorder[i]);
    }
    //Rebulid Binary Tree from Inorder and Postorder
    TreeNode* root = bulidTreeFromInPost(inorder, postorder, n);
    //Zigzag Level Order Traversal
    ZigzagLevelOrder(root, n);
    free(root);
    return 0;
}