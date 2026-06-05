# Fundamentals of Data Structures (FDS) 学习记录

这里是我在学习《数据结构基础》课程时积累的代码、作业和课程项目。
为了方便管理和编译，项目主体使用 C 语言编写，并通过 CMake 进行了简单的模块化构建。希望这份记录能作为很好的复习资料。

## 📂 目录结构

整个仓库主要分为四个部分：

### 1. 数据结构与算法实现 (`fds data structures and algorithums/`)
这是本仓库的核心部分，包含了课上学到的各类基础数据结构和图论算法的代码实现。通过 CMake 统一管理，支持跨文件的头文件调用。
* **Graph (图论)**: 
  * 存储结构：邻接表、邻接矩阵、边集数组等。
  * 最短路径：Dijkstra、SPFA、Bellman-Ford。
  * 最小生成树：Prim、Kruskal (结合了并查集)。
  * 网络流：Edmonds-Karp、最大容量路径算法等。
  * 拓扑排序与关键路径。
* **Sort (排序)**: 包含了冒泡、插入、选择、希尔 (Shell)、归并 (Merge)、快速排序 (Quick) 和堆排序的实现。
* **Tree (树)**: 二叉树的各种遍历与重建、二叉搜索树 (BST)、线段树等。
* **其他基础结构**: 最小堆 (`heap`)、并查集 (`disjoint set union`)、哈希表 (`hash table`)、以及栈和队列的链式/顺序实现。

### 2. 经典习题与练习 (`fds probelms/`)
收录了一些课程相关的经典算法题和课后练习的解法，用于巩固特定知识点：
* Maximum Subarray (最大子段和)
* Complete Binary Search Tree (完全二叉搜索树)
* Tree Traversals (树的遍历变体，如 Z 字形遍历)
* Two Pointer (双指针技巧应用)

### 3. 课程大作业 (`project1/` ~ `project3/`)
包含了课程要求完成的三个主要 Project。
每个目录下均包含完整的源代码 (`src/` 或 `code/`) 以及对应的分析与实验报告 (`report/`)。

### 4. 辅助脚本 (`scripts/`)
写了一个简单的 PowerShell 脚本 (`auto_sync.ps1`)，配合 Windows 计划任务使用，用于在后台定期将本地代码更改自动推送到 GitHub，当作一个自动备份工具。

## ⚙️ 编译与运行指南

本项目主体 (`fds data structures and algorithums` 目录下) 使用 **CMake** 进行构建，以解决多文件 C 语言项目的编译问题。

**环境要求**：
* CMake (>= 3.10)
* GCC / MinGW 编译器

**在 VS Code 中运行**：
1. 推荐安装微软官方的 `CMake Tools` 插件。
2. 打开项目根目录后，按 `Ctrl + Shift + P` 唤出命令面板，输入 `CMake: Run Without Debugging`。
3. 在弹出的目标列表中选择你想要运行的测试程序（例如 `test_prim`、`sort_merge` 等），即可自动完成编译并运行。

---
*Note: 本仓库仅作个人学习、复习与代码备份使用。*