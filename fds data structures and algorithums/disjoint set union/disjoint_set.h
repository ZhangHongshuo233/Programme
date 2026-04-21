#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <stdio.h>
#include <stdlib.h>

typedef struct DisjointSet {
    int *parent;
    int size;
}DisjointSet;

DisjointSet* CreateDisjointSet(int size);
int Find(DisjointSet* ds, int x);
void Union(DisjointSet* ds, int root1, int root2);
void DestroyDisjointSet(DisjointSet *ds);


#endif // DISJOINT_SET_H