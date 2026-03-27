#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hstable.h"
//哈希表实现，使用链式地址法
//每个桶使用链表存储冲突的元素


//简单的哈希函数，基于djb2算法
unsigned int hash(const HashTable* table, const char* key) {
    unsigned int hash_value = 0;
    while (*key) {
        hash_value = (hash_value << 5) + *key++;
    }
    return hash_value % table->capacity;
}

//创建哈希表
HashTable* CreateTable(int capacity) {
    if (capacity <= 0) {
        printf("Invalid table size.\n");
        return NULL;
    }
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    table->buckets = (node**)malloc(sizeof(node*) * capacity);
    if (table->buckets == NULL) {
        printf("Memory allocation failed.\n");
        free(table);
        return NULL;
    }
    for (int i = 0; i < capacity; i++) {
        table->buckets[i] = NULL;
    }
    table->size = 0;
    table->capacity = capacity;
    return table;
}

//创建新节点
node* CreateNode(const char* key, int val) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return NULL;
    }
    new_node->key = strdup(key);
    if (new_node->key == NULL) {
        printf("Memory allocation failed.\n");
        free(new_node);
        return NULL;
    }
    /*
    new_node->key = (char*)malloc(strlen(key) + 1);
    if (new_node->key == NULL) {
        printf("Memory allocation failed.\n");
        free(new_node);
        return NULL;
    }   
    strcpy(new_node->key, key);
    */
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

//插入或更新元素
void Insert(HashTable* table,const char* key, int val) {
    if(table == NULL || key == NULL){
        printf("Invalid input.\n");
        return;
    }
    unsigned int idx = hash(table, key);
    node* current = table->buckets[idx];
    //update value if key already exists
    while(current != NULL){
        if(strcmp(current->key, key) == 0){
            current->val = val;
            return;
        }   
        current = current->next;
    }
    //insert new node if key does not exist(头插法)
    node* new_node = CreateNode(key, val);
    if (new_node == NULL) {
        printf("Failed to create node.\n");
        return;
    }
    new_node->next = table->buckets[idx];
    table->buckets[idx] = new_node;
    table->size++;
}

//查找元素，返回值并通过found参数指示是否找到
int Get(const HashTable* table, const char* key, int* found){
    if(table == NULL || key == NULL || found == NULL){
        printf("Invalid input.\n");
        return -1;
    }
    unsigned int idx = hash(table, key);
    node* current = table->buckets[idx];
    while(current != NULL){
        if(strcmp(current->key, key) == 0){
            *found = 1;
            return current->val;
        }
        current = current->next;
    }
    if(*found == 0){
        printf("Key '%s' not found.\n", key);
        return 0;
    }
}

//删除元素，返回1表示成功删除，返回0表示未找到，返回-1表示输入无效
int Remove(HashTable* table, const char* key){
    //return 1 if deletion is successful, return 0 if key not found, return -1 if input is invalid

    if(table == NULL || key == NULL){
        printf("Invalid input.\n");
        return -1;
    }
    unsigned int idx = hash(table, key);
    node* current = table->buckets[idx];
    node* prev = NULL;
    while(current != NULL){
        if(strcmp(current->key, key) == 0){
            if(prev == NULL){
                //if prev is NULL, current is the head of the list
                table->buckets[idx] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current->key);
            free(current);
            table->size--;
            return 1;
        }
        prev = current;
        current = current->next;
    }

    printf("Key '%s' not found.\n", key);
    return 0;
}

// 检查键是否存在
int containsKey(HashTable* table, const char* key) {
    int found = 0;
    Get(table, key, &found);
    return found;
}

//打印哈希表内容
void PrintTable(const HashTable* table){
    if(table == NULL){
        printf("Invalid input.\n");
        return;
    }
    printf("Hash Table (size: %d, capacity: %d):\n", table->size, table->capacity);
    for(int i=0;i<table->capacity;i++){
        node* current = table->buckets[i];
        if(current != NULL){
            printf("Bucket %d: \n", i);
            while(current != NULL){
                printf("Key = '%s', Value = %d\n", current->key, current->val);
                current = current->next;
            }
            printf("\n");
        }
    }
}

//清空哈希表
void Clear(HashTable* table){
    if(table == NULL){
        return ;
    }
    for(int i=0;i<table->capacity;i++){
        node* current = table->buckets[i];
        while(current){
            node* temp = current;
            current = current->next;
            free(temp->key);
            free(temp);
        }
        table->buckets[i] = NULL;
    }
    table->size = 0;
}

//销毁哈希表
void DestroyTable(HashTable* table){
    if(table == NULL){
        return ;
    }
    Clear(table);
    free(table->buckets);
    free(table);
}

