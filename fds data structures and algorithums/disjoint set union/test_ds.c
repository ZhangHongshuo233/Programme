#include <stdio.h>
#include "disjoint_set.h"

// 辅助函数：窥探并查集的内部阵法（打印数组内容）
void PrintDisjointSet(DisjointSet* ds) {
    printf("当前数组状态 (索引: 父节点/大小):\n");
    for (int i = 1; i <= ds->size; i++) {
        printf("[%d]: %2d  ", i, ds->parent[i]);
    }
    printf("\n\n");
}

int main() {
    int n = 6; // 假设武林中有 6 位大侠，编号 1 到 6
    printf("========== ⚔️ 并查集测试：武林门派结盟 ⚔️ ==========\n\n");

    DisjointSet* ds = CreateDisjointSet(n);
    printf("--> 初始状态：每个人自成一派，都是掌门（大小为 -1）\n");
    PrintDisjointSet(ds);

    printf("--> 事件 1：1号 和 2号 结盟 (Union 1, 2)\n");
    Union(ds, 1, 2);
    PrintDisjointSet(ds);

    printf("--> 事件 2：3号 和 4号 结盟 (Union 3, 4)\n");
    Union(ds, 3, 4);
    PrintDisjointSet(ds);

    printf("--> 查询：1号 和 4号 是同一个门派的吗？\n");
    if (Find(ds, 1) == Find(ds, 4)) {
        printf("答案：是！\n\n");
    } else {
        printf("答案：不是。\n\n");
    }

    printf("--> 事件 3：2号 和 3号 结盟 (Union 2, 3)，两大阵营合并！\n");
    printf("    (注意观察：Smart Union 会把小门派合并到大门派中)\n");
    Union(ds, 2, 3);
    PrintDisjointSet(ds);

    printf("--> 再次查询：1号 和 4号 是同一个门派的吗？\n");
    if (Find(ds, 1) == Find(ds, 4)) {
        printf("答案：是！他们现在都听命于同一个掌门。\n\n");
    } else {
        printf("答案：不是。\n\n");
    }

    printf("--> 事件 4：5号加入 4号的门派 (Union 4, 5)\n");
    Union(ds, 4, 5);
    PrintDisjointSet(ds);

    printf("--> 神级优化：路径压缩 (Path Compression) 展示\n");
    printf("    目前 5号 的直接上级可能不是最终掌门，现在我们单独查找一下 5号 (Find 5)\n");
    int root_of_5 = Find(ds, 5);
    printf("    5号的最终掌门是: %d\n", root_of_5);
    printf("    请注意看下面数组的变化，5号在查找时，顺手把自己直接连到了掌门名下！\n");
    PrintDisjointSet(ds);

    DestroyDisjointSet(ds);
    printf("========== 测试结束，内存已释放 ==========\n");

    return 0;
}