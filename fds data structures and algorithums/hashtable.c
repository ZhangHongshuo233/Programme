#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

hs_table* CreateTable(int len){  //tlen be prime number to reduce collisions
    if(len <= 0){
        printf("Invalid table length.\n");
        return NULL;
    }
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
    while(1){
        if(table->head[idx].occupied == 0){
            printf("数据 %d 未找到(探测 %d 次)\n",
                    data->val, probe_cnt);
            return -1;
        }
        if(table->head[idx].occupied == 1 && table->head[idx].val == data->val){
            printf("数据 %d 找到，所在下标 %d, 线性探测次数 %d\n",
                    data->val, idx, probe_cnt);
            return idx;
        }
        probe_cnt++;
        idx = (idx + 1) % table->tlen;
        if(idx == org_idx){
            printf("数据 %d 未找到(探测 %d 次)\n",
                    data->val, probe_cnt);
            return -1;
        }
    }
}

int Delete(hs_table* table, datatype* data){
    if(table == NULL || data == NULL){
        printf("Invalid input.\n");
        return -1;
    }
    int idx = Search(table, data);
    if(idx < 0){
        printf("数据 %d 删除失败，未找到。\n", data->val);
        return -1;
    }
    table->head[idx].occupied = -1;
    table->cnt--;
    printf("数据 %d 删除成功，删除下标 %d\n", data->val, idx);
    return 0;
}

int Resize(hs_table* table, int new_tlen){
    if(table == NULL || new_tlen <= table->cnt){
        printf("扩容参数无效（新长度需大于原长度）\n");
        return -1; 
    }
    hs_table* new_table = Create(new_tlen);
    if(new_table == NULL){
        printf("Failed to create new hash table for resizing.\n");
        return -1;
    }
    for(int i = 0; i < table->tlen; i++){
        // Only rehash occupied slots
        if(table->head[i].occupied == 1){
            Insert(new_table, &table->head[i]);
        }
    }
    free(table->head);
    table->head = new_table->head;
    table->tlen = new_table->tlen;
    free(new_table);
    printf("Hash table resized to new length %d, LoadFactor: %.2f\n", 
            new_tlen, LoadFactor(table));
    return 0;
}