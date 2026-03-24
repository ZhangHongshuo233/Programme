#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct datatype{
    int val; 
    int occupied; // 0 for empty, 1 for occupied, -1 for deleted    
}datatype;

typedef struct{
    datatype* head;
    int tlen;
    int cnt;
}hs_table;

hs_table* CreateTable(int tlen);
int Insert(hs_table* table, datatype* data);
int Search(hs_table* table, datatype* data);
int Delete(hs_table* table, datatype* data);
float LoadFactor(hs_table* table);
int Resize(hs_table* table, int new_tlen);
int DestroyTable(hs_table* table);

#endif // HASHTABLE_H