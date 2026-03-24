#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

hs_table* Create(int len){  //tlen be prime number to reduce collisions
    hs_table* table = (hs_table*)malloc(sizeof(hs_table));
    if(table == NULL){
        printf("Memory allocation failed.\n");
        return NULL;
    }
    table->head = (datatype*)malloc(sizeof(datatype)*len);
    if(table->head == NULL){
        printf("Memory allocation failed.\n");
        free(table);
        return NULL;
    }
    table->tlen = len;
    table->cnt = 0;
    for(int i = 0; i < len; i++){
        table->head[i].occupied = 0; // Mark all slots as empty
    }
    return table;
}

int hashfunc(hs_table* table, datatype* data){
    if(table == NULL || data == NULL){
        printf("Invalid input.\n");
        return -1;
    }
    int key = data->val;
    key =key < 0 ? -key : key; // Ensure non-negative
    return key % table->tlen;
}

float LoadFactor(hs_table* table){
    if(table == NULL || table->tlen == 0){
        return 0.0f;
    }
    return (float)table->cnt / table->tlen;
}

int Insert(hs_table* table, datatype* data){
    //check the parameters
    if(table == NULL || data == NULL){
        printf("Invalid input.\n");
        return -1;
    }

    //check the load factor
    if(LoadFactor(table) >= 0.75f){
        printf("LoadFactor %.2f >= 0.75,it's suggested to resize the table.\n", LoadFactor(table));
    }

    //calculate the hash index
    int idx = hashfunc(table,data);
    if(idx < 0){
        return -1; 
    }
    int org_idx = idx; // Store original index 
    int probe_cnt = 0; // To count the number of probes

    // Collision resolution using linear probing(线性探测解决冲突)
    while(table->head[idx].occupied == 1){ 
        probe_cnt++;
        printf("数据 %d 冲突，冲突下标 %d, 向后探测...(第 %d 次)\n", 
                data->val, idx, probe_cnt);
        idx = (idx + 1) % table->tlen;
        if(idx == org_idx){
            printf("Hash table is full, insertion dailed.\n");
            return -1; 
        }     
    } 
    table->head[idx] = *data;
    table->head[idx].occupied = 1;
    table->cnt++;
    printf("数据 %d 插入成功，插入下标 %d, 线性探测次数 %d\n", 
            data->val, idx, probe_cnt);
    return 0;
}

int Search(hs_table* table, datatype* data){
    if(table == NULL || data == NULL){
        printf("Invalid input.\n");
        return -1;
    }
    int idx = hashfunc(table,data);
    if(idx < 0){
        return -1; 
    }
    int org_idx = idx;
    int probe_cnt = 0;
    while(table->head[idx] != *data){
        probe_cnt++;
        idx = (idx + 1) % table->tlen;
        if(idx == org_idx){
            printf("数据 %d 未找到(探测 %d 次)\n", 
                    data->val, probe_cnt);
            return -1;
        }
    }
    printf("数据 %d 找到，所在下标 %d, 线性探测次数 %d\n", 
            data->val, idx, probe_cnt);
    return idx;
}