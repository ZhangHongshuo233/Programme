#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "search.h"  
#include <limits.h>

typedef struct {
    int iterations_k;
    clock_t ticks;
    double total_time_sec;
    double duration_sec;
} MeasureResult;

// Measure one algorithm and return all timing metrics.
MeasureResult measure_time(int (*func)(int*, int, int), int* arr, int n, int key){
    clock_t start,end;
    clock_t ticks;
    //initial number of repetitions
    int K = 1; 

    //we need to find the proper K such that the total ticks is at least 10
    do{
        start = clock();    //record the start time

        //run the search function for K times
         for(int i=0;i<K;i++){
            (*func)(arr, n, key); 
        }

        end = clock();      //record the end time
        
        ticks = end - start;   //calculate the total ticks for K repetitions

        //if the total ticks is less than 10, that means the time is too short to be measured accurately, so we need to double K to get a more accurate measurement
        if(ticks < 10){
            K *= 2;
        }
    }while(ticks < 10 );  // K should not exceed INT_MAX/2 to prevent overflow 
    
    //formally measure the running time with the determined K
    start = clock();
    for(int i=0;i<K;i++){
        (*func)(arr, n, key);
    }
    end = clock();

    MeasureResult result;
    result.iterations_k = K;
    result.ticks = end - start;
    result.total_time_sec = (double)result.ticks / CLOCKS_PER_SEC;
    result.duration_sec = result.total_time_sec / K;
    return result;
}

static void print_result(const char* name, MeasureResult result) {
    printf("%-22s\t%8d\t%8ld\t%8.6f\t%e\n",
           name,
           result.iterations_k,
           (long)result.ticks,
           result.total_time_sec,
           result.duration_sec);
}

static void write_result_csv(FILE* fp, int n, const char* name, MeasureResult result) {
    fprintf(fp, "%d,%s,%d,%ld,%.9f,%e\n",
            n,
            name,
            result.iterations_k,
            (long)result.ticks,
            result.total_time_sec,
            result.duration_sec);
}

int main(){
    //define the test sizes for the performance measurement
    int test_sizes[] = {100, 500, 1000, 2000, 4000, 6000, 8000, 10000};
    int num_sizes = sizeof(test_sizes) / sizeof(test_sizes[0]);

    //define arrays to store the results for each search algorithm and test size
    MeasureResult result_seq_Iterative[num_sizes];
    MeasureResult result_seq_Recursive[num_sizes];
    MeasureResult result_bin_Iterative[num_sizes];
    MeasureResult result_bin_Recursive[num_sizes];

    printf("Starting performance measurement...\n");

    //for each test size, we will create a sorted array of that size and measure the performance of each search algorithm on it
    for (int i = 0; i < num_sizes; i++) {
        int N = test_sizes[i];

        //define an array of size N and fill it with sorted values from 0 to N-1
        int* arr = (int*)malloc(N * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed when N=%d\n", N);
            exit(1);
        }
        for (int j = 0; j < N; j++) {
            arr[j] = j;
        }

        int key = N;   //worst case: the key is not in the array

        //measure the performance of each search algorithm and get the timing metrics
        result_seq_Iterative[i]= measure_time(seqSearch_Iterative, arr, N, key);
        result_seq_Recursive[i] = measure_time(seqSearch_Recursive, arr, N, key);
        result_bin_Iterative[i] = measure_time(binSearch_Iterative, arr, N, key);
        result_bin_Recursive[i] = measure_time(binSearch_Recursive, arr, N, key);

        free(arr);
    }

    printf("\n=== Final Result Table ===\n");
    printf("N\tAlgorithm\t\t\tIterations (K)\tTicks\tTotal Time (sec)\tDuration (sec)\n");

    for (int i = 0; i < num_sizes; i++) {
        printf("%d\t", test_sizes[i]);
        print_result("seqSearch_Iterative", result_seq_Iterative[i]);

        printf("\t");
        print_result("seqSearch_Recursive", result_seq_Recursive[i]);

        printf("\t");
        print_result("binSearch_Iterative", result_bin_Iterative[i]);

        printf("\t");
        print_result("binSearch_Recursive", result_bin_Recursive[i]);

        printf("--------------------------------------------------------------------------------\n");
    }

    //To export the results to a CSV file for further analysis, we can write the results into a file named "benchmark_results.csv"
    /*To achieve this,you just need to choose from line 137 to line 152 
    and uncomment them, then run the program again, 
    and it will generate the CSV file in the same directory as the program.
    You can open the CSV file with Excel or any other spreadsheet software to analyze the results more conveniently.*/

    // FILE* csv = fopen("benchmark_results.csv", "w");
    // if (csv == NULL) {
    //     printf("Failed to create benchmark_results.csv\n");
    //     return 1;
    // }

    // fprintf(csv, "N,Algorithm,Iterations (K),Ticks,Total Time (sec),Duration (sec)\n");
    // for (int i = 0; i < num_sizes; i++) {
    //     write_result_csv(csv, test_sizes[i], "seqSearch_Iterative", result_seq_Iterative[i]);
    //     write_result_csv(csv, test_sizes[i], "seqSearch_Recursive", result_seq_Recursive[i]);
    //     write_result_csv(csv, test_sizes[i], "binSearch_Iterative", result_bin_Iterative[i]);
    //     write_result_csv(csv, test_sizes[i], "binSearch_Recursive", result_bin_Recursive[i]);
    // }

    // fclose(csv);
    // printf("\nResults exported to benchmark_results.csv\n");

    return 0;
}
