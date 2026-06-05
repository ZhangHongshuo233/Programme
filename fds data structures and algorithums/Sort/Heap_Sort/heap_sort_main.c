#include <stdio.h>
extern void heap_sort(int* arr, int n);

int main(){
    int arr[] = {5,3,8,4,2,7,1,6};
    int n = sizeof(arr)/sizeof(arr[0]);
    heap_sort(arr, n);
    for(int i=0;i<n;i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
