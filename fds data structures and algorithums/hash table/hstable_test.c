#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hstable.h"


int main() {
    // 创建哈希表
    HashTable* table = CreateTable(10);
    printf("哈希表已创建\n\n");
    
    // 插入数据
    Insert(table, "apple", 5);
    Insert(table, "banana", 8);
    Insert(table, "orange", 12);
    Insert(table, "grape", 3);
    Insert(table, "watermelon", 20);
    
    printf("插入5个元素后:\n");
    PrintTable(table);
    printf("\n");
    
    // 获取数据
    int found;
    int value = Get(table, "banana", &found);
    if (found) {
        printf("banana = %d\n", value);
    } else {
        printf("banana 不存在\n");
    }
    
    value = Get(table, "mango", &found);
    if (found) {
        printf("mango = %d\n", value);
    } else {
        printf("mango 不存在\n");
    }
    printf("\n");
    
    // 更新数据
    Insert(table, "apple", 10);
    printf("更新 apple 后:\n");
    value = Get(table, "apple", &found);
    printf("apple = %d\n\n", value);
    
    // 删除数据
    Remove(table, "grape");
    printf("删除 grape 后，大小: %d\n", table->size);
    printf("grape 是否存在: %s\n\n", containsKey(table, "grape") ? "是" : "否");
    
    // 再次打印
    PrintTable(table);
    
    // 清空并销毁
    Clear(table);
    printf("\n清空后大小: %d\n", table->size);
    
    DestroyTable(table);
    printf("哈希表已销毁\n");
    
    return 0;
}