#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1000

static int arr[MAXN];   
static int pos =0;
typedef struct seqque{
    int* data;
    int front;
    int rear;
}seqque;

seqque* queue_create(){
    seqque* queue = (seqque*)malloc(sizeof(seqque));
    queue->data = (int*)malloc(MAXN * sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    return queue;
}

void Enqueue(seqque* queue, int val){
    if(queue == NULL || queue->rear == MAXN - 1){
        return;
    }
    queue->data[++queue->rear] = val;
}

void Dequeue(seqque* queue){
    if(queue == NULL || queue->rear < queue->front){
        return;
    }
    queue->front++;
}

int queue_is_empty(seqque* queue){
    return queue == NULL || queue->rear < queue->front;
}

int queue_front(seqque* queue){
    if(queue == NULL || queue_is_empty(queue)){
        return -1; 
    }
    return queue->data[queue->front];
}

void queue_destroy(seqque* queue){
    if(queue != NULL){
        free(queue->data);
        free(queue);
    }
}

typedef struct Node{
    int key;
    int left;
    int right;
}Node;

typedef struct CBST{
    Node nodes[MAXN];
}CBST;

CBST* tree_create(int n){
    CBST* tree = (CBST*)malloc(sizeof(CBST));
    for(int i = 0; i < n; i++){
        tree->nodes[i].key = 0;
        tree->nodes[i].left = (2*i + 1 < n) ? (2*i + 1) : -1;
        tree->nodes[i].right = (2*i + 2 < n) ? (2*i + 2) : -1;
    }
    return tree;
}

void inorder_traversal(CBST* tree, int index){
    if(index == -1) return;
    inorder_traversal(tree, tree->nodes[index].left);
    tree->nodes[index].key = arr[pos++];
    inorder_traversal(tree, tree->nodes[index].right);
}

void tree_destroy(CBST* tree){
    if(tree == NULL) return;
    free(tree);
}

void LevelOrderTraversal(CBST* tree){
    seqque* queue = queue_create();
    Enqueue(queue, 0);
    int first = 1;
    while(!queue_is_empty(queue)){
        int cur = queue_front(queue);
        Dequeue(queue);
        if(first){
            first = 0;
        }else{
            printf(" ");
        }
        printf("%d", tree->nodes[cur].key);

        if(tree->nodes[cur].left != -1){
            Enqueue(queue, tree->nodes[cur].left);
        }
        if(tree->nodes[cur].right != -1){
            Enqueue(queue, tree->nodes[cur].right);
        }
    }
    queue_destroy(queue);
}
    
int cmp(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}
int main(){
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, n, sizeof(int), cmp);
    CBST* tree = tree_create(n);
    inorder_traversal(tree, 0);
    LevelOrderTraversal(tree);
    tree_destroy(tree);
    return 0;
}