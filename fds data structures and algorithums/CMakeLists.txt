# 指定 CMake 的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 定义项目名称和使用的语言 (C语言)
project(FDS_Algorithms C)

# 设置 C 语言标准为 C99
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

# ==========================================
# 1. 配置全局头文件搜索路径 (Include Directories)
# 把你截图里的所有底层数据结构文件夹都加进来！
# ==========================================
include_directories(
    "disjoint set union"
    "hash table"
    "heap"
    "linklist"
    "queue"
    "Sort"
    "stack"
    "tree"
    "graph/Adjacency List"
    "graph/Edge List"
)

# ==========================================
# 2. 图论算法部分的测试程序 (保留我们之前写好的)
# ==========================================

# 测试 SPFA 算法
add_executable(test_spfa
    "graph/Adjacency List/adj_list.c"
    "graph/Adjacency List/shortest_path/spfa_path.c"
)

# 测试 Bellman-Ford 算法
add_executable(test_bellman
    "graph/Edge List/edge_list.c"
    "graph/Edge List/shortest_path/bellman_ford.c"
)

# 测试 Kruskal 算法 (跨目录联合编译)
add_executable(test_kruskal
    "disjoint set union/disjoint_set.c"
    "graph/Edge List/edge_list.c"
    "graph/Edge List/minimum_spanning_tree/kruskal_mst.c"
)

# 测试 Dijkstra 算法
add_executable(test_dijkstra
    "graph/Adjacency List/adj_list.c"
    "heap/min_heap.c"
    "graph/Adjacency List/shortest_path/dijkstra_path.c"
)

# ==========================================
# 3. 未来新数据结构的测试模板 (供后续使用)
# ==========================================
# 当你写好了栈(stack)的代码，想测试它时，可以取消下面这行的注释：
# add_executable(test_stack "stack/stack.c" "stack/test_stack.c")

# 当你写好了树(tree)的代码，可以这样配置：
# add_executable(test_tree "tree/tree.c" "tree/test_tree.c")