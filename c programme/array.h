#ifndef _ARRAY_H
#define _ARRAY_H
#include <stdlib.h>
#include <string.h>

const int BLOCK_SIZE =20;

typedef struct {
    int *array;
    int size;
} Array;

Array array_create (int  init_size) {
    Array a;
    a.array = (int*)malloc(sizeof(int) * init_size);
    a.size = init_size;
    return a;
}

void array_free(Array *a){
    free(a->array);
    a->array=NULL;
    a->size =0;
}

void array_inflate(Array *a, int more_size){

    //手动复制
    // int* p=(int*)malloc(sizeof(int)*(a->size+more_size));
    // int i;
    // for(i=0;i<a->size;i++){
    //     p[i]=a->array[i];
    // }
    // free(a->array);
    // a->array=p;

    int*p =(int*)malloc(sizeof(int)*(a->size+more_size));
    memcpy(p,a->array,sizeof(int)*a->size);
    free(a->array);
    a->array=p;
    a->size+=more_size;
}

//  封装
int array_size (const Array *a){
     return a->size;
}

int* array_at(Array*a, int index){
    if(index>(a->size)){
        array_inflate(a,(index/BLOCK_SIZE+1)*BLOCK_SIZE-a->size);
    }
    return &(a->array[index]); 
}

int array_get(Array *a, int index){
    return a->array[index];
}
   
void array_set(Array *a, int index, int value){
    a->array[index] = value;
}

// void array_inflate(Array *a, int more_size){
//     a->array = (int*)realloc(a->array, sizeof(int)*(a->size + more_size));
//     a->size += more_size;
// }


// Array array_create (int  init_size);
// void array_free(Array *a);
// int array_size(const Array *a);
// int* array_at(Array *a, int index);
// void array_inflate(Array *a, int more_size);

#endif