#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#define MAX_SIZE 100
// 主函数测试
int main()
{
    // 创建长度为11（质数）的哈希表
    hs_table* table = CreateTable(11);
    if (table == NULL)
    {
        return -1;
    }
    // 定义测试数据
    int len = 10;
    datatype a[MAX_SIZE];
    for (int i = 0; i < len; i++)
    {
        a[i].val = i * 10 + 7; // 生成一些测试数据，如7, 17, 27, ...
    }
    // 插入数据
    for (int i = 0; i < len; i++)
    {
        Insert(table, &a[i]);
    }
    // 打印负载因子
    printf("当前负载因子：%.2f\n", LoadFactor(table));
    // 扩容哈希表（新长度23，质数）
    Resize(table, 23);
    // 查询数据67
    int want_num = 67;
    datatype search_data = {want_num, 0}; // 只需要val字段，occupied不影响查询
    int ret = Search(table, &search_data);
    // 删除数据67
    Delete(table, &search_data);
    // 再次查询67（验证删除）
    Search(table, &search_data);
    // 销毁哈希表
    DestroyTable(table);
    return 0;
}