#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

typedef struct Node{
    int val;
    char* key;
    struct Node* next;
}node;

typedef struct HashTable{
    node** buckets;
    int size;
    int capacity;
}HashTable;

unsigned int hash(const HashTable* table, const char* key);
HashTable* CreateTable(int capacity);
node* CreateNode(const char* key, int val);
void Insert(HashTable* table, const char* key, int val);
int Get(const HashTable* table, const char* key, int* found);
int Remove(HashTable* table, const char* key);
int ContainKey(const HashTable* table, const char* key);
void PrintTable(const HashTable* table);
void Clear(HashTable* table);
void DestroyTable(HashTable* table);

#endif // _HASHTABLE_H_