#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ──────────────────────────────────────────────────────────────
   Constants
   ────────────────────────────────────────────────────────────── */
#define MAXN 200001     /* maximum number of nodes per tree */
#define HASH_SIZE (1 << 20)       /* hash table capacity: 1 048 576(2^20) slots */
#define HASH_MASK (HASH_SIZE - 1) /* bit-mask for fast modulo (Usually, the HASH_MASK is set as the power of 2 minus 1)*/
#define EMPTY     0x80000001LL    /* sentinel for "empty" slot (out of int range) */
/* 
 * Some interesting brainstorming about hash design:
 * 1.HASH_SIZE (1 << 20):given that the amount of input data is up to 2e5,
 *   if the hash_size is set to 2^20, then the load factor is about 0.2, which is acceptable.
 * 2.EMPTY 0x80000001LL :
 *  At first, I set EMPTY to (long long)(2e9 + 1), which is out of the range of input scale(-2e9 to 2e9), to avoid collision with valid keys,
 *  but then I realized that 0x80000001LL maybe a better choice,
 *  because it is out of int range, hhh.
 */


/* ──────────────────────────────────────────────────────────────
   BST Node
   ────────────────────────────────────────────────────────────── */
typedef struct Node{
    long long key;  /* node key value */
    int left;       /* index of left child (-1 = none) */
    int right;      /* index of right child (-1 = none) */
} Node;

/* tree representation:
 *  here we use array-based instead of pointer-based structure to represent the BSTs,
 *  because the input nodes are marked by index, so we can visit them directly via array indexing without needing to follow pointer links.
 *  This also allows us to avoid dynamic memory allocation for nodes, which can be more efficient and simpler in this context.
 */

/* ──────────────────────────────────────────────────────────────
   Global storage
   ────────────────────────────────────────────────────────────── */
static Node BST1[MAXN];          /* nodes of BST1                       */
static Node BST2[MAXN];          /* nodes of BST2                       */

/* Inorder result for BST1 (sorted keys in ascending order, but duplicates kept)         */
static long long inorder1[MAXN];
static int       inorder1_size = 0;

/* Preorder result                                        */
static long long preorder1[MAXN], preorder2[MAXN];
static int       preorder1_size = 0, preorder2_size = 0;

/* ──────────────────────────────────────────────────────────────
   Hash Table Operations
   ────────────────────────────────────────────────────────────── */
typedef struct hs_table{
    long long* head;
    int tlen;
    int cnt;
} hs_table;

/*
 * hash_init – fill every slot with the EMPTY sentinel.
 * Time: O(HASH_SIZE)
 */
static void hash_init(hs_table* table){
    if(table == NULL){
        printf("Invalid input.\n");
        return;
    }
    for (int i = 0; i < table->tlen; i++)
        table->head[i] = EMPTY;
}

/*
 * hash_create – allocate and initialize a hash table with given length.
 * Returns pointer to the new table, or NULL on failure.
 */
static hs_table* hash_create(int len){
    if(len <= 0){
        printf("Invalid table length.\n");
        return NULL;
    }
    hs_table* table = (hs_table*)malloc(sizeof(hs_table));
    if(table == NULL){
        printf("Memory allocation failed.\n");
        return NULL;
    }
    table->head = (long long*)malloc(sizeof(long long) * len);
    if(table->head ==NULL){
        printf("Memory allocation failed.\n");
        free(table);
        return NULL;
    }
    table->tlen = len;
    table->cnt = 0;
    hash_init(table);
    return table;
}

/*
 * hash_func – map a key to a slot index.
 * We XOR the high and low 32 bits for better distribution of
 * large negative keys, then mask to [0, HASH_SIZE).
 * tips: 
 *  1.we can also use other hash functions, but this one is simple and effective for our key range.
 *  2.we can use inline to suggest the compiler to optimize it, since it will be called frequently.
 *  (This is not important for correctness, just a performance hint.)
 */
static int hash_func(long long key){
    unsigned long long u = (unsigned long long)key;
    u ^= (u >> 32);
    return (int)(u & HASH_MASK);
}

/*
 * hash_insert – insert key into the hash table.
 * Using Open addressing with linear probing; skips if already present.
 */
static void hash_insert(hs_table* table, long long key){
    //check the parameters
    if(table == NULL){
        printf("Invalid input.\n");
        return;
    }
    //calculate the hash index
    int idx = hash_func(key);
    //store the original index to detect full table
    int org_idx = idx;
    if(idx < 0){
        printf("Hash function error.\n");
        return;
    }   
    while(table->head[idx] != EMPTY && table->head[idx] != key){
        idx = (idx + 1) & HASH_MASK;
        if(idx == org_idx){
            printf("Hash table is full, insertion failed.\n");
            return;
        }
    }
    table->head[idx] = key;
    table->cnt++;
}

/*
 * hash_search – return 1 if key exists in the table, 0 otherwise.
 */
static int hash_search(hs_table* table, long long key){
    if(table == NULL){
        printf("Invalid input.\n");
        return 0;
    }
    int idx = hash_func(key);
    if(idx < 0){
        printf("Hash function error.\n");
        return 0;
    }
    int org_idx = idx;
    while(1){
        /* Nessary explaint for the logic of linear probing search:
         * As for linear probing, the space between the original index and the first EMPTY after it will be occupied by keys that hash to the same index
         * if 'original index' is EMPTY, it means there is no such key that appears at this index, so we can conclude the key is not in the table.
        */
        if(table->head[idx] == EMPTY){
            return 0;
        }
        else if(table->head[idx] == key){
            return 1;
        }
        idx = (idx + 1) & HASH_MASK;
        if(idx == org_idx){
            return 0;
        }
    }
    return 0;
}

static void hash_destroy(hs_table* table){
    if(table == NULL){
        return;
    }
    free(table->head);
    free(table);
}

/* ──────────────────────────────────────────────────────────────
   Tree Building
   ────────────────────────────────────────────────────────────── */

/*
 * build_tree – read n nodes from stdin, construct BST in array t[].
 *
 * Input format (per node i):
 *   key  parentIndex   (parentIndex == -1 means root)
 *
 * We first store all (key, parentIndex) pairs, 
 * then wire up left/right pointers by inserting each child into its parent
 * according to BST rules:
 *   key < parent.key  → left child
 *   key >= parent.key → right child
 *
 * Returns the index of the root node.
 */

static int tree_create(Node tree[], int n){
    long long keys[MAXN];
    int par[MAXN];
    int root = -1;
    //Read all nodes and initialise left/right to "no child"
    for(int i=0;i<n;i++){
        scanf("%lld %d",&keys[i],&par[i]);
        tree[i].key = keys[i];
        tree[i].left = -1;
        tree[i].right = -1;
        if(par[i] == -1){
            root = i;
        }
    }

    //Build the link between parent and child nodes
    for(int i=0;i<n;i++){
        if(par[i] == -1){
            continue; //skip root
        }else{
            int p = par[i];
            //Insert the child node into its parent according to BST rules
            if(tree[i].key < tree[p].key){
                //goes to left subtree
                tree[p].left = i;
            }else{
                //goes to right subtree
                tree[p].right = i;
            }
        }
    }

    return root;
}

/* ──────────────────────────────────────────────────────────────
    Stack-based Tree Traversals (to avoid stack overflow on large n)
    ────────────────────────────────────────────────────────────── */

typedef struct stack{
    int stk[MAXN];
    int top;
}stack;

static void stack_init(stack* s){
    s->top = -1;
}

stack* stack_create(){
    stack* s = (stack*)malloc(sizeof(stack));
    if(s == NULL){
        printf("Memory allocation failed.\n");
        return NULL;
    }
    stack_init(s);
    return s;
}

static void stack_push(stack* s, int val){
    if(s->top >= MAXN - 1){
        printf("Stack overflow.\n");
        return;
    }
    int top = s->top + 1;
    s->top = top;
    s->stk[top] = val;
}

static void stack_pop(stack* s){
    if(s->top < 0){
        printf("Stack underflow.\n");
        return;
    }
    s->top--;
}

static int stack_top(stack* s){
    if(s->top < 0){
        printf("Stack is empty.\n");
        return -1;
    }
    int top = s->top;
    return s->stk[top];
}

static void stack_destroy(stack* s){
    free(s);
}

static int stack_is_empty(stack* s){
    return s->top < 0;
}

/* ──────────────────────────────────────────────────────────────
   Tree Traversals  (iterative to avoid stack overflow on large n)
   ────────────────────────────────────────────────────────────── */

/*
 * inorder – iterative(i.e. non-recursive):
 *  in-order traversal of BST tree[] rooted at root.
 *  Appends keys to the global inorder1[] array.
 * In a BST, in-order gives keys in non-decreasing order.
 */
static void inorder(Node tree[], int root){
    stack* stack = stack_create();
    if(root == -1){
        stack_destroy(stack);
        return;
    }
    int cur = root;
    while(cur != -1 || stack_is_empty(stack) == 0){
        //push all left children to stack
        while(cur != -1){
            stack_push(stack, cur);
            cur = tree[cur].left;
        }
        //Visit root node 
        cur = stack_top(stack);
        stack_pop(stack);
        inorder1[inorder1_size++] = tree[cur].key;
        //Move to right subtree
        cur = tree[cur].right;
    }
    stack_destroy(stack);
}

/*
 * preorder – iterative pre-order traversal of tree t[] rooted at root.
 * Appends keys to buf[]; *size is updated.
 */
static void preorder(Node tree[], int root, long long buf[], int* size){
    stack* stack = stack_create();
    if(root == -1){
        stack_destroy(stack);
        return;
    }
    stack_push(stack, root);
    while(stack_is_empty(stack) == 0){
        //Visit root node
        int cur = stack_top(stack);
        stack_pop(stack);
        buf[(*size)++] = tree[cur].key;
        //Push right child first so left is processed first
        if(tree[cur].right != -1){
            stack_push(stack, tree[cur].right);
        }
        //Push left child
        if(tree[cur].left != -1){
            stack_push(stack, tree[cur].left);
        }
    }
    stack_destroy(stack);
}

 /* ──────────────────────────────────────────────────────────────
   Map T2's keys into hash table (via inorder traversal)
   ────────────────────────────────────────────────────────────── */
static void map_tree_to_hash(Node tree[], int root, hs_table* table){
    stack* stack = stack_create();
    if(root == -1){
        stack_destroy(stack);
        return;
    }
    int cur = root;
    while(cur != -1 || stack_is_empty(stack) == 0){
        while(cur != -1){
            stack_push(stack, cur);
            cur = tree[cur].left;
        }
        cur = stack_top(stack);
        stack_pop(stack);
        hash_insert(table, tree[cur].key);
        cur = tree[cur].right;
    }
}

/* ──────────────────────────────────────────────────────────────
   Main Program
   ────────────────────────────────────────────────────────────── */
int main(void){
    int n1,n2;
    /* ── Step 1: Read and build BST1 ── */
    scanf("%d",&n1);
    int root1 = tree_create(BST1, n1);

    /* ── Step 2: Read and build BST2 ── */
    scanf("%d",&n2);
    int root2 = tree_create(BST2, n2);

    /* ── Step 3: Read target N ── */
    long long N;
    scanf("%lld",&N);

    /* ── Step 4: Inorder traversal of BST1 → key array ── */
    inorder(BST1, root1);   /* (in ascending order due to the properties of binary search tree) */

    /* ── Step 5: Insert all T2's keys into hash table ── */
    hs_table* table = hash_create(HASH_SIZE);
    map_tree_to_hash(BST2, root2, table);

    /* ── Step 6: Find all pairs(A,B) such that A + B = N ──
     * For each unique A, we check whether (N - A) exists in BST2's hash.
     * We skip consecutive duplicates to satisfy "same equation once".
     */
    /* Temporary result storage: store A values that form a solution */
    long long res[MAXN];
    int res_size = 0;
    for(int i=0;i<inorder1_size;i++){
        /* skip duplicates */
        if(i > 0 && inorder1[i] == inorder1[i-1]){
            continue;
        }
        long long a = inorder1[i];
        long long b = N - a;
        if(hash_search(table, b)){
            res[res_size++] = a;
        }
    }

    /* ── Step 7: Output results ── */
    if(res_size == 0){
        printf("false\n");
    }else{
        printf("true\n");
        for (int i = 0; i < res_size; i++)
            printf("%lld = %lld + %lld\n", N, res[i], N - res[i]);
    }

    /* ── Step 8: Preorder traversals of T1,T2── */
    preorder(BST1, root1, preorder1, &preorder1_size);
    preorder(BST2, root2, preorder2, &preorder2_size);

    /* Print T1 preorder */
    for(int i=0;i<preorder1_size;i++) {
        if(i > 0){
            printf(" ");
        }
        printf("%lld", preorder1[i]);
    }
    printf("\n");

    /* Print T2 preorder */
    for(int i=0;i<preorder2_size;i++) {
        if(i > 0){
            printf(" ");
        }
        printf("%lld", preorder2[i]);
    }
    printf("\n");

    return 0;
}