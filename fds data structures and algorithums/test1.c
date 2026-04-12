#include <stdio.h>
#include <stdlib.h>

#define MinData -1

typedef int ElementType;

typedef struct HeapStruct *PriorityQueue;
struct HeapStruct {
    ElementType  *Elements;
    int Capacity;
    int Size;
};
void PercolateUp( int p, PriorityQueue H ){
    if(H == NULL || p <= 0 || p > H->Size){
        return;
    }

    for(int i = p; i > 1 && H->Elements[i/2] > H->Elements[i] ; i /= 2){
        ElementType temp = H->Elements[i];
        H->Elements[i] = H->Elements[i/2];
        H->Elements[i/2] = temp;
    }
}
void PercolateDown( int p, PriorityQueue H ){
    if(H == NULL || p <= 0 || p > H->Size){
        return;
    }
    int child;
    for(int i = p; (child = i * 2) <= H->Size; i *= 2){
        if(child + 1 <= H->Size && H->Elements[child] > H->Elements[child + 1]){
            child++;
        }
        if(H->Elements[i] > H->Elements[child]){
            ElementType temp = H->Elements[i];
            H->Elements[i] = H->Elements[child];
            H->Elements[child] = temp;
        }else{
            break;
        }
    }
}

