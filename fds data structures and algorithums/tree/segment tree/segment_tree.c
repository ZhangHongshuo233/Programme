#include <stdio.h>

#define MAX_NODES 100 // 为安全起见，通常线段树数组开到原数组大小的 4 倍即可

int tree[MAX_NODES]; // 线段树数组
int A[] = {7, 2, 5, 8, 3}; // 课件上的原始测试数组

/* 1. 构建线段树 */
void Build(int node, int start, int end) {
    // Base Case: 叶子节点
    if (start == end) {
        tree[node] = A[start];
        return;
    }
    
    // Recursive Step: 拆分并构建左右子树
    int mid = (start + end) / 2;
    Build(2 * node, start, mid);          // 左子树节点编号为 2*node
    Build(2 * node + 1, mid + 1, end);    // 右子树节点编号为 2*node + 1
    
    // Merge Logic: 当前节点等于左右子节点之和
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}
 
/* 2. 区间查询 */
int Query(int node, int start, int end, int L, int R) {
    // Case 1: 完全无交集 (No Overlap)
    if (R < start || end < L) {
        return 0;
    }
    
    // Case 2: 完全被包含 (Total Overlap)
    if (L <= start && end <= R) {     
        return tree[node];
    }
    
    // Case 3: 部分交集 (Partial Overlap)，需要深入左右子树
    int mid = (start + end) / 2;
    int left_sum = Query(2 * node, start, mid, L, R);
    int right_sum = Query(2 * node + 1, mid + 1, end, L, R);
    
    return left_sum + right_sum;
}

/* 3. 单点更新 */
void Update(int node, int start, int end, int idx, int val) {
    // Base Case: 找到具体的叶子节点
    if (start == end) {
        tree[node] = val;
        A[idx] = val; // 同步更新原数组 (可选)
        return;
    }
    
    // Recursive Step: 判断索引 idx 在左边还是右边
    int mid = (start + end) / 2;
    if (start <= idx && idx <= mid) {
        // 索引在左子树
        Update(2 * node, start, mid, idx, val);
    } else {
        // 索引在右子树
        Update(2 * node + 1, mid + 1, end, idx, val);
    }
    
    // Backtracking Step: 子树更新后，回溯更新当前节点
    tree[node] = tree[2 * node] + tree[2 * node + 1];
}

int main() {
    int n = sizeof(A) / sizeof(A[0]);
    
    // 注意：根节点编号一般从 1 开始，方便利用 2*node 和 2*node+1 计算左右孩子
    Build(1, 0, n - 1);
    
    printf("Original sum of range [0, 2]: %d\n", Query(1, 0, n - 1, 0, 2)); // 预期: 7+2+5 = 14
    printf("Original sum of range [2, 4]: %d\n", Query(1, 0, n - 1, 2, 4)); // 预期: 5+8+3 = 16
    
    // 测试单点更新：把 A[3] 的值从 8 改为 9 (课件中的例子)
    printf("\nUpdating index 3 to value 9...\n");
    Update(1, 0, n - 1, 3, 9);
    
    printf("New sum of range [2, 4]: %d\n", Query(1, 0, n - 1, 2, 4)); // 预期: 5+9+3 = 17
    printf("New total sum [0, 4]: %d\n", Query(1, 0, n - 1, 0, 4));    // 预期: 7+2+5+9+3 = 26
    
    return 0;
}