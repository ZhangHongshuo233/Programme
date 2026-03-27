#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hstable.h"


int main() {
    // 创建哈希表
    HashTable* table = createHashTable(10);
    printf("哈希表已创建\n\n");
    
    // 插入数据
    put(table, "apple", 5);
    put(table, "banana", 8);
    put(table, "orange", 12);
    put(table, "grape", 3);
    put(table, "watermelon", 20);
    
    printf("插入5个元素后:\n");
    printHashTable(table);
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
    put(table, "apple", 10);
    printf("更新 apple 后:\n");
    value = Get(table, "apple", &found);
    printf("apple = %d\n\n", value);
    
    // 删除数据
    removeKey(table, "grape");
    printf("删除 grape 后，大小: %d\n", size(table));
    printf("grape 是否存在: %s\n\n", containsKey(table, "grape") ? "是" : "否");
    
    // 再次打印
    printHashTable(table);
    
    // 清空并销毁
    clear(table);
    printf("\n清空后大小: %d\n", size(table));
    
    destroyHashTable(table);
    printf("哈希表已销毁\n");
    
    return 0;
}