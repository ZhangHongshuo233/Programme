#include <stdio.h>
#include <stdlib.h>
#include "search.h"

//helper function to run all the test cases for a given search function
void run_test_case(int id, int* arr, int n, int key, int expected){
    int result;
    //test sequential search (iterative)
    result = seqSearch_Iterative(arr, n, key);
    printf("TC%02d seqSearch_Iterative: expected %d, got %d -> %s\n", id, expected, result, result == expected ? "PASS" : "FAIL");

    //test sequential search (recursive)
    result = seqSearch_Recursive(arr, n, key);
    printf("TC%02d seqSearch_Recursive: expected %d, got %d -> %s\n", id, expected, result, result == expected ? "PASS" : "FAIL");

    //test binary search (iterative)
     result = binSearch_Iterative(arr, n, key);
    result = binSearch_Iterative(arr, n, key);
    printf("TC%02d binSearch_Iterative: expected %d, got %d -> %s\n", id, expected, result, result == expected ? "PASS" : "FAIL");

    //test binary search (recursive)
    result = binSearch_Recursive(arr, n, key);
    printf("TC%02d binSearch_Recursive: expected %d, got %d -> %s\n", id, expected, result, result == expected ? "PASS" : "FAIL");

    printf("\n");
}

int main(){
    int arr1[] = {0,1,2,3,4,5,6,7,8,9};
    
    // TC01: Normal case, exist
    run_test_case(1, arr1, 10, 5, 5);

    // TC02: Left boundary
    run_test_case(2, arr1, 10, 0, 0);

    // TC03: Right boundary
    run_test_case(3, arr1, 10, 9, 9);

    // TC04: None existence
    run_test_case(4, arr1, 10, 10, -1);

    // TC05: Minimum scale, exist
    int arr2[] = {0};
    run_test_case(5, arr2, 1, 0, 0);

    // TC06: Minimum scale, none existence
    run_test_case(6, arr2, 1, 1, -1);

    // TC07: Large scale, exist
    int N = 10000;
    int* arr3 = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++){
        arr3[i] = i;
    }
    run_test_case(7, arr3, N, 5000, 5000);

    // TC08: Large scale, none existence
    run_test_case(8, arr3, N, N, -1);
    free(arr3);

    // TC09: NULL pointer
    run_test_case(9, NULL, 10, 5, -1);

    // TC10: n=0
    int dummy;
    run_test_case(10, &dummy, 0, 5, -1);

    return 0;
}
