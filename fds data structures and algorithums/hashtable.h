#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct data{
    int val;
}datatype;

typedef struct{
    datatype* head;
    int tlen;
    int cnt;
}hs_table;

hs_table* create_table(int tlen);
int Insert(hs_table* table, int val);
int Search(hs_table* table, int val);
int Delete(hs_table* table, int val);
float LoadFactor(hs_table* table);
int Resize(hs_table* table, int new_tlen);
int Destroy(hs_table* table);

#endif // HASHTABLE_H