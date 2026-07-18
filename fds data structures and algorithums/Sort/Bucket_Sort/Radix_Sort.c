#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10 // 十进制共有 10 个桶 (0-9) (PPT 第 11 页)

// 链表单节点定义（用于桶内部挂载）
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 获取数字在当前位（exp）上的数值。例如 exp=1 是个位，exp=10 是十位
int GetDigit(int num, int exp) {
    return (num / exp) % 10;
}

// 次位优先基数排序 (LSD Radix Sort)
void RadixSort(int A[], int N) {
    // 找出数组中的最大值，用以确定最大位数
    int max_val = A[0];
    for (int i = 1; i < N; i++) {
        if (A[i] > max_val) max_val = A[i];
    }

    // 建立 10 个桶的头尾指针数组
    Node *bucket_head[BUCKET_SIZE] = {NULL};
    Node *bucket_tail[BUCKET_SIZE] = {NULL};

    // 从个位开始 (exp = 1)，每次乘以 10 向上跃迁
    for (int exp = 1; max_val / exp > 0; exp *= 10) {
        
        // 1. 分配阶段 (Pass): 将数组元素依次倒进对应的桶里
        for (int i = 0; i < N; i++) {
            int digit = GetDigit(A[i], exp);
            
            Node *new_node = (Node *)malloc(sizeof(Node));
            new_node->data = A[i];
            new_node->next = NULL;
            
            if (bucket_head[digit] == NULL) {
                bucket_head[digit] = new_node;
            } else {
                bucket_tail[digit]->next = new_node;
            }
            bucket_tail[digit] = new_node;
        }

        // 2. 收集阶段: 按顺序将 0-9 号桶里的元素倒回原数组
        int array_idx = 0;
        for (int b = 0; b < BUCKET_SIZE; b++) {
            Node *curr = bucket_head[b];
            while (curr != NULL) {
                A[array_idx++] = curr->data;
                Node *temp = curr;
                curr = curr->next;
                free(temp); // 顺手释放内存
            }
            // 倒空后重置桶指针
            bucket_head[b] = NULL;
            bucket_tail[b] = NULL;
        }
    }
}

int main() {
    int arr[] = {64, 8, 216, 512, 27, 729, 0, 1, 343, 125}; // PPT 第 10 页标准样例数据
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original input:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    RadixSort(arr, n);

    printf("\nOutput (LSD Radix Sorted):\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}    