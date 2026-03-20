#include <stdio.h>
int is_local_max(int matrix[][20],int i,int j){
    int cur = matrix[i][j];
    if(cur>matrix[i-1][j]&&cur>matrix[i+1][j]&&
       cur>matrix[i][j-1]&&cur>matrix[i][j+1]){
        return 1;
    }
    else{
        return 0;
    }
}
int main() {
    int M, N;
    int i,j;
    int found=0;
    // 读入矩阵的行数和列数
    scanf("%d %d", &M, &N);
    int matrix[20][20];
    // 读入矩阵元素
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    // 查找并输出局部最大值及其位置
    for(i=1;i<M-1;i++){
        for(j=1;j<N-1;j++){
            if(is_local_max(matrix,i,j)){
                found=1;
                printf("%d %d %d\n",matrix[i][j],i,j);
            }
        }
        
    }    
    if(!found){
        printf("None %d %d\n",M,N);
    }
    return 0;
}