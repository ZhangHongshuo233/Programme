#include<stdio.h>
int main(){
    int i,j,n,k;
    scanf("%d",&n);
    int a[n][n];
    //initialize and read elements into the matrix
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            scanf("%d",&a[i][j]);
        }
    }
    int found=0;
    //find and print the saddle points
    for(i=0;i<n;i++){
        int max_val = a[i][0];
        for(j=1; j<n; j++){
            if(a[i][j] > max_val) max_val = a[i][j];
        }

        for(j=0; j<n; j++){
            if(a[i][j] == max_val){
                int is_min = 1;
                for(k=0; k<n; k++){
                    if(a[k][j] < a[i][j]){
                        is_min = 0;
                        break;
                    }
                }
                if(is_min){
                    printf("%d %d\n", i, j);
                    found = 1;
                }
            }
        }
    }
    if(!found){
        printf("NONE");
    }
    return 0;


}