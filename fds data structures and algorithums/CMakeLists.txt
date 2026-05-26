# 1. 基础设置
cmake_minimum_required(VERSION 3.10)
project(FDS_Algorithms C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# ==========================================
# 2. 全局头文件搜索路径 (Include Directories)
# 这样在任何代码里都可以直接 #include "xxx.h"
# ==========================================
include_directories(
    "disjoint set union"
    "hash table"
    "heap/binary heap"
    "heap/binary heap/min_heap"
    "linklist"
    "queue"
    "stack"
    "Sort"
    "tree/binary search tree"
    "tree/binary tree"
    "tree/segment tree"
    "graph/Adjacency List"
    "graph/Edge List"
    "graph/Adjacency Multilist"
)

# ==========================================
# 3. 编译目标集结号 (Executables)
# 格式：add_executable(运行程序名 源文件1 源文件2 ...)
# ==========================================

# ----------------- [1] 图论算法 (Graph) -----------------
add_executable(test_spfa         "graph/Adjacency List/adj_list.c" "graph/Adjacency List/shortest_path/spfa_path.c")
add_executable(test_dijkstra     "graph/Adjacency List/adj_list.c" "heap/binary heap/min_heap/min_heap.c" "graph/Adjacency List/shortest_path/dijkstra_path.c")
add_executable(test_bellman      "graph/Edge List/edge_list.c" "graph/Edge List/shortest_path/bellman_ford.c")
add_executable(test_kruskal      "graph/Edge List/edge_list.c" "disjoint set union/disjoint_set.c" "graph/Edge List/minimum_spanning_tree/kruskal_mst.c")
add_executable(test_topological  "graph/Adjacency List/adj_list.c" "graph/Adjacency List/topological_sort/topological_sort.c")
add_executable(test_cpm "graph/Adjacency List/adj_list.c" "graph/Adjacency List/topological_sort/critical_path.c")
add_executable(test_ff_naive    "graph/Network Flow/ford_fulkerson_naive.c")
add_executable(test_ek          "graph/Network Flow/edmonds_karp.c")
add_executable(test_max_cap     "graph/Network Flow/max_capacity_path.c")
add_executable(test_mcmf        "graph/Network Flow/min_cost_max_flow.c")
add_executable(test_prim        "graph/Adjacency List/adj_list.c" "graph/Adjacency List/minimum_spanning_tree/prim_mst.c" "heap/binary heap/min_heap/min_heap.c")



# ----------------- [2] 基础数据结构测试 -----------------
# 栈与队列
add_executable(test_stack    "stack/linkstack.c" "stack/Stack_test.c")
add_executable(test_linkque  "queue/linkque.c" "queue/linkque_test.c")

# 链表
add_executable(test_doulink  "linklist/doulink.c" "linklist/doulink_test.c")

# 哈希表
add_executable(test_hashtable "hash table/hashtable.c" "hash table/hashtable_test.c")
add_executable(test_hstable   "hash table/hstable.c" "hash table/hstable_test.c")

# 并查集
add_executable(test_ds "disjoint set union/disjoint_set.c" "disjoint set union/test_ds.c")

# 二叉堆
add_executable(test_heap_insert "heap/binary heap/heap_operations.c" "heap/binary heap/test_insertion.c")
add_executable(test_heap_linear "heap/binary heap/heap_operations.c" "heap/binary heap/test_linear.c")

# ----------------- [3] 树结构 (Tree) -----------------
# 编译二叉树时，将跨目录联合全局的 queue 和 stack 一起编译！
add_executable(test_bintree 
    "tree/binary tree/binary tree.c" 
    "tree/binary tree/RebuildTree.c" 
    "tree/binary tree/main.c" 
    "queue/linkque.c" 
    "stack/linkstack.c"
)

# ----------------- [4] 排序算法 (Sort) -----------------
# 假设你的每一个排序文件里都有自己独立的 main 函数
add_executable(sort_bubble    "Sort/Bubble_Sort.c")
add_executable(sort_heap      "Sort/Heap_Sort.c")
add_executable(sort_insertion "Sort/Insertion_Sort.c")
add_executable(sort_quick     "Sort/Quick_Sort.c")
add_executable(sort_selection "Sort/Selection_Sort.c")