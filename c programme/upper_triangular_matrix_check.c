#include<stdio.h>
int main(){
    int i,j,k,T,n;
    // Read number of test cases
    scanf("%d",&T);
    for(i=0;i<T;i++){
        // Flag to check if matrix is upper triangular
        int is_upper_triangular=1;
        // Read size of the matrix
        scanf("%d",&n);
        int a[n][n];
        for(j=0;j<n;j++){
            for(k=0;k<n;k++){
                scanf("%d",&a[j][k]);
            }
        } 
        // Check for upper triangular property
        for(j=0;j<n;j++){
            for(k=0;k<j;k++){
                // If any element below the main diagonal is non-zero
                if(a[j][k]!=0){
                    is_upper_triangular=0;
                    break;
                }
            }
        }  
        // Output result based on the flag
        printf(is_upper_triangular ? "YES\n" : "NO\n");
    }
    return 0;
}