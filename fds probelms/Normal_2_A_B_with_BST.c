#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int parent;
    int left;
    int right;
} Node;

static int BuildTree(Node *nodes, int n)
{
    int root = -1;

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &nodes[i].key, &nodes[i].parent);
        nodes[i].left = -1;
        nodes[i].right = -1;
    }

    for (int i = 0; i < n; i++) {
        if (nodes[i].parent == -1) {
            root = i;
            continue;
        }

        int parent = nodes[i].parent;
        if (nodes[i].key < nodes[parent].key) {
            nodes[parent].left = i;
        } else {
            nodes[parent].right = i;
        }
    }

    return root;
}

static int CollectInOrder(const Node *nodes, int root, int *values, int n)
{
    int *stack = (int *)malloc(sizeof(int) * n);
    if (stack == NULL) {
        return 0;
    }

    int top = -1;
    int count = 0;
    int cur = root;

    while (top != -1 || cur != -1) {
        while (cur != -1) {
            stack[++top] = cur;
            cur = nodes[cur].left;
        }

        cur = stack[top--];
        values[count++] = nodes[cur].key;
        cur = nodes[cur].right;
    }

    free(stack);
    return count;
}

static void PrintPreOrder(const Node *nodes, int root, int n)
{
    int *stack = (int *)malloc(sizeof(int) * n);
    if (stack == NULL) {
        return;
    }

    int top = -1;
    int first = 1;

    stack[++top] = root;
    while (top != -1) {
        int cur = stack[top--];
        if (!first) {
            printf(" ");
        }
        printf("%d", nodes[cur].key);
        first = 0;

        if (nodes[cur].right != -1) {
            stack[++top] = nodes[cur].right;
        }
        if (nodes[cur].left != -1) {
            stack[++top] = nodes[cur].left;
        }
    }

    printf("\n");
    free(stack);
}

static void PrintPairs(const int *a, int n1, const int *b, int n2, long long target)
{
    int i = 0;
    int j = n2 - 1;
    int found = 0;

    while (i < n1 && j >= 0) {
        long long sum = (long long)a[i] + (long long)b[j];

        if (sum == target) {
            printf("%d + %d = %lld\n", a[i], b[j], target);
            found = 1;

            int leftValue = a[i];
            int rightValue = b[j];
            while (i < n1 && a[i] == leftValue) {
                i++;
            }
            while (j >= 0 && b[j] == rightValue) {
                j--;
            }
        } else if (sum < target) {
            int leftValue = a[i];
            while (i < n1 && a[i] == leftValue) {
                i++;
            }
        } else {
            int rightValue = b[j];
            while (j >= 0 && b[j] == rightValue) {
                j--;
            }
        }
    }

    if (!found) {
        printf("No Solution\n");
    }
}

int main(void)
{
    int n1;
    int n2;
    long long target;

    if (scanf("%d", &n1) != 1) {
        return 0;
    }

    Node *tree1 = (Node *)malloc(sizeof(Node) * n1);
    if (tree1 == NULL) {
        return 0;
    }

    int root1 = BuildTree(tree1, n1);

    if (scanf("%d", &n2) != 1) {
        free(tree1);
        return 0;
    }

    Node *tree2 = (Node *)malloc(sizeof(Node) * n2);
    if (tree2 == NULL) {
        free(tree1);
        return 0;
    }

    int root2 = BuildTree(tree2, n2);

    if (scanf("%lld", &target) != 1) {
        free(tree1);
        free(tree2);
        return 0;
    }

    int *in1 = (int *)malloc(sizeof(int) * n1);
    int *in2 = (int *)malloc(sizeof(int) * n2);
    if (in1 == NULL || in2 == NULL) {
        free(tree1);
        free(tree2);
        free(in1);
        free(in2);
        return 0;
    }

    int len1 = CollectInOrder(tree1, root1, in1, n1);
    int len2 = CollectInOrder(tree2, root2, in2, n2);

    PrintPairs(in1, len1, in2, len2, target);
    PrintPreOrder(tree1, root1, n1);
    PrintPreOrder(tree2, root2, n2);

    free(tree1);
    free(tree2);
    free(in1);
    free(in2);
    return 0;
}