#include"array.h"
#include <stdlib.h>
#include <stdio.h>


// typedef struct {
//     int *array;
//     int size;
// } Array;


int main(){
    Array a = array_create(100);
    printf("size=%d\n", array_size(&a));
    *array_at(&a, 10) = 123;
    printf("a[10]=%d\n", *array_at(&a, 10));
    int num=0;
    int cnt=0;
    while(num!=-1){
        scanf("%d",&num);
        if(num!=-1)
        *array_at(&a,cnt++)=num;
    }
    array_free(&a);
    return 0;
}
    