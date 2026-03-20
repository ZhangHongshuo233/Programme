#include<stdio.h>
#include<stdlib.h>
//reverse function to reverse a portion of the array
void reverse(int a[],int left,int right){
    while(left<right){
        int temp=a[left];
        a[left++]=a[right];
        a[right--]=temp;
    }
}
//complexity O(n) time and O(1) space
void right_rotate(int a[],int n,int m){
    int k=m%n;
    if(k==0) return;
    reverse(a,0,n-1);
    reverse(a,0,k-1);
    reverse(a,k,n-1);
}
//main function
int main() {
    int m, n, i, j;
    scanf("%d %d", &m, &n);
    
    //allocate memory for 2D array
    int **a = (int **)malloc(n * sizeof(int *));
    
    //check for memory allocation failure
    if (a == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    //allocate memory for each row
    for (i = 0; i < n; i++) {
        a[i] = (int *)malloc(n * sizeof(int));
        //check for memory allocation failure
        if (a[i] == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }
    }
    
    //read input for 2D array
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    
    // rotate each row
    for (i = 0; i < n; i++) {
        right_rotate(a[i], n, m); 
    }
    //output the rotated array
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            //ensure no extra space at the end of each line
            if (j == 0) {
                printf("%d", a[i][j]);
            } else {
                printf(" %d", a[i][j]);
            }
        }
        printf("\n"); 
    }
    //free allocated memory
    for (i = 0; i < n; i++) {
        free(a[i]);
    }
    free(a);
    return 0;
    
}
////the previous version with O(n*m) complexity
// void right_rotate(int a[],int n,int m){
//     int i,j,temp;
//     for(i=0;i<m;i++){
//         temp=a[n-1];
//         for(j=n-1;j>0;j--){
//             a[j]=a[j-1];
//         }
//         a[0]=temp;
//     }
// }
// int main(){
//     int m,n,i,j;
//     //读入数组元素个数及元素值
//     scanf("%d %d",&m,&n);
//     m=m%n;
//     int a[n][n];
//     for(i=0;i<n;i++){
//         for(j=0;j<n;j++){
//             scanf("%d",&a[i][j]);
//         }   
//     }

//     int(*p)[n]=a;
//     for(i=0;i<n;i++){
//         right_rotate(p+i,n,m);
//     }

//     //输出右移后的数组元素
//     for(i=0;i<n;i++){
//         for(j=0;j<n;j++){
//             if(j==0){
//                 printf("%d",a[i][j]);
//             }else{
//                 printf(" %d",a[i][j]);
//             }
//         }
//         if(i!=n-1)
//         printf("\n");
//     }
// }

// //allocate memory for 2D array
// #include<stdio.h>
// #include<stdlib.h>
// int**a=(int**)malloc(n*sizeof(int*));
// if(a==NULL){
//     printf("Memory allocation failed!\n");
//     return 1;
// }
// //allocate memory for each row
// for(i=0;i<n;i++){
//     a[i]=(int*)malloc(n*sizeof(int));
//     //check for memory allocation failure
//     if(a[i]==NULL){
//         printf("Memory allocation failed!\n");
//         return 1;
//     }
// }
// //free allocated memory
// for(i=0;i<n;i++){
//     free(a[i]);
// }
// free(a);
