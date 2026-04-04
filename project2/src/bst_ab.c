/*
 * ============================================================
 *  Project: Normal-2  A+B with Binary Search Trees
 *  Course : Fundamentals of Data Structure and Algorithm
 *  Author : (Your Name)
 *  Date   : 2025
 * ============================================================
 *
 *  Problem Summary:
 *    Given two BSTs T1 and T2, and an integer N, find all pairs
 *    (A, B) where A ∈ T1, B ∈ T2, and A + B = N.
 *    Output results in ascending order of A (no duplicates).
 *    Finally, print the preorder traversal of both trees.
 *
 *  Strategy:
 *    1. Build both BSTs from the parent-index input format.
 *    2. Collect T1 keys via in-order traversal → sorted array A[].
 *    3. Collect T2 keys into a hash set for O(1) look-up.
 *    4. For each unique A[i], check if (N - A[i]) exists in T2's hash set.
 *    5. Print preorder traversals of T1 and T2.
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ──────────────────────────────────────────────────────────────
   Constants
   ────────────────────────────────────────────────────────────── */
#define MAXN      200005          /* maximum number of nodes per tree */
#define HASH_SIZE (1 << 20)       /* hash table capacity: 1 048 576 slots */
#define HASH_MASK (HASH_SIZE - 1) /* bit-mask for fast modulo              */
#define EMPTY     0x80000001LL    /* sentinel for "empty" slot (out of int range) */

/* ──────────────────────────────────────────────────────────────
   BST Node
   ────────────────────────────────────────────────────────────── */
typedef struct {
    long long key;   /* node key value                   */
    int  left;       /* index of left  child (-1 = none) */
    int  right;      /* index of right child (-1 = none) */
} Node;

/* ──────────────────────────────────────────────────────────────
   Global storage
   ────────────────────────────────────────────────────────────── */
static Node tree1[MAXN];          /* nodes of T1                       */
static Node tree2[MAXN];          /* nodes of T2                       */

/* In-order result for T1 (sorted keys, duplicates kept)         */
static long long inorder1[MAXN];
static int       inorder1_size = 0;

/* Preorder result buffers                                        */
static long long pre1[MAXN], pre2[MAXN];
static int       pre1_size = 0, pre2_size = 0;

/* Hash table for T2 keys (open addressing, linear probing)      */
static long long hash_table[HASH_SIZE];

/* ──────────────────────────────────────────────────────────────
   Hash Table Operations
   ────────────────────────────────────────────────────────────── */

/*
 * hash_init – fill every slot with the EMPTY sentinel.
 * Time: O(HASH_SIZE)
 */
static void hash_init(void)
{
    for (int i = 0; i < HASH_SIZE; i++)
        hash_table[i] = EMPTY;
}

/*
 * hash_fn – map a key to a slot index.
 * We XOR the high and low 32 bits for better distribution of
 * large negative keys, then mask to [0, HASH_SIZE).
 */
static inline int hash_fn(long long key)
{
    unsigned long long u = (unsigned long long)key;
    u ^= (u >> 32);
    return (int)(u & HASH_MASK);
}

/*
 * hash_insert – insert key into the hash table.
 * Uses linear probing; skips if already present.
 */
static void hash_insert(long long key)
{
    int idx = hash_fn(key);
    while (hash_table[idx] != EMPTY && hash_table[idx] != key)
        idx = (idx + 1) & HASH_MASK;
    hash_table[idx] = key;        /* inserts OR overwrites with same value */
}

/*
 * hash_search – return 1 if key exists in the table, 0 otherwise.
 */
static int hash_search(long long key)
{
    int idx = hash_fn(key);
    while (hash_table[idx] != EMPTY) {
        if (hash_table[idx] == key) return 1;
        idx = (idx + 1) & HASH_MASK;
    }
    return 0;
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
 * We first store all (key, parentIndex) pairs, then wire up
 * left/right pointers by inserting each child into its parent
 * according to BST rules:
 *   key < parent.key  → left child
 *   key >= parent.key → right child
 *
 * Returns the index of the root node.
 */
static int build_tree(Node t[], int n)
{
    /* Temporary storage: keys and parent indices                 */
    long long keys[MAXN];
    int       par[MAXN];
    int       root = -1;

    /* Initialise left/right to "no child"                       */
    for (int i = 0; i < n; i++) {
        t[i].left  = -1;
        t[i].right = -1;
    }

    /* Read all nodes                                             */
    for (int i = 0; i < n; i++) {
        scanf("%lld %d", &keys[i], &par[i]);
        t[i].key = keys[i];
        if (par[i] == -1) root = i;
    }

    /* Wire parent-child links                                    */
    for (int i = 0; i < n; i++) {
        int p = par[i];
        if (p == -1) continue;           /* skip root            */
        if (keys[i] < t[p].key)
            t[p].left  = i;              /* goes to left subtree */
        else
            t[p].right = i;             /* goes to right subtree */
    }

    return root;
}

/* ──────────────────────────────────────────────────────────────
   Tree Traversals  (iterative to avoid stack overflow on large n)
   ────────────────────────────────────────────────────────────── */

/*
 * inorder – iterative in-order traversal of tree t[] rooted at root.
 * Appends keys to the global inorder1[] array.
 * In a BST, in-order gives keys in non-decreasing order.
 */
static void inorder(Node t[], int root)
{
    /* Explicit stack to simulate recursion                       */
    int stk[MAXN];
    int top = 0;
    int cur = root;

    while (cur != -1 || top > 0) {
        /* Go as far left as possible                             */
        while (cur != -1) {
            stk[top++] = cur;
            cur = t[cur].left;
        }
        /* Visit node on top of stack                             */
        cur = stk[--top];
        inorder1[inorder1_size++] = t[cur].key;
        /* Move to right subtree                                  */
        cur = t[cur].right;
    }
}

/*
 * preorder – iterative pre-order traversal of tree t[] rooted at root.
 * Appends keys to buf[]; *size is updated.
 */
static void preorder(Node t[], int root, long long buf[], int *size)
{
    int stk[MAXN];
    int top = 0;

    if (root == -1) return;
    stk[top++] = root;

    while (top > 0) {
        int cur = stk[--top];
        buf[(*size)++] = t[cur].key;
        /* Push right first so left is processed first            */
        if (t[cur].right != -1) stk[top++] = t[cur].right;
        if (t[cur].left  != -1) stk[top++] = t[cur].left;
    }
}

/* ──────────────────────────────────────────────────────────────
   Collect T2 keys into hash set (via in-order traversal)
   ────────────────────────────────────────────────────────────── */

/*
 * collect_t2_hash – traverse T2 in-order and insert every key
 * into the hash table (duplicates are silently handled).
 */
static void collect_t2_hash(Node t[], int root)
{
    int stk[MAXN];
    int top = 0;
    int cur = root;

    while (cur != -1 || top > 0) {
        while (cur != -1) {
            stk[top++] = cur;
            cur = t[cur].left;
        }
        cur = stk[--top];
        hash_insert(t[cur].key);
        cur = t[cur].right;
    }
}

/* ──────────────────────────────────────────────────────────────
   Main Program
   ────────────────────────────────────────────────────────────── */
int main(void)
{
    int n1, n2;
    long long N;

    /* ── Step 1: Read and build T1 ── */
    scanf("%d", &n1);
    int root1 = build_tree(tree1, n1);

    /* ── Step 2: Read and build T2 ── */
    scanf("%d", &n2);
    int root2 = build_tree(tree2, n2);

    /* ── Step 3: Read target N ── */
    scanf("%lld", &N);

    /* ── Step 4: In-order traversal of T1 → sorted key array ── */
    inorder(tree1, root1);

    /* ── Step 5: Insert all T2 keys into hash set ── */
    hash_init();
    collect_t2_hash(tree2, root2);

    /* ── Step 6: Find all pairs A + B = N ──
     *
     * We walk inorder1[] (sorted ascending).
     * For each unique A, we check whether (N - A) exists in T2's hash.
     * We skip consecutive duplicates to satisfy "same equation once".
     */
    /* Temporary result storage: store A values that form a solution */
    long long results[MAXN];
    int       results_size = 0;

    long long prev_a = EMPTY;          /* track last A to skip duplicates */
    for (int i = 0; i < inorder1_size; i++) {
        long long a = inorder1[i];
        if (a == prev_a) continue;     /* duplicate A – skip              */
        prev_a = a;
        long long b = N - a;
        if (hash_search(b))
            results[results_size++] = a;
    }

    /* ── Step 7: Output results ── */
    if (results_size == 0) {
        printf("false\n");
    } else {
        printf("true\n");
        for (int i = 0; i < results_size; i++)
            printf("%lld = %lld + %lld\n", N, results[i], N - results[i]);
    }

    /* ── Step 8: Preorder traversals ── */
    preorder(tree1, root1, pre1, &pre1_size);
    preorder(tree2, root2, pre2, &pre2_size);

    /* Print T1 preorder */
    for (int i = 0; i < pre1_size; i++) {
        if (i > 0) printf(" ");
        printf("%lld", pre1[i]);
    }
    printf("\n");

    /* Print T2 preorder */
    for (int i = 0; i < pre2_size; i++) {
        if (i > 0) printf(" ");
        printf("%lld", pre2[i]);
    }
    printf("\n");

    return 0;
}
