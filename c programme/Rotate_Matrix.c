#include<stdio.h>
#include<stdlib.h>
//the first solution:
// Time Complexity: O(N^2)
// Space Complexity: O(N^2) - Requires extra memory
void rotate_matrix_1(int** matrix,int size){
    int i,j;
    //allocate memory for 2D array
    int**rotated =(int**)malloc(size*sizeof(int*));

    //check for memory allocation failure
    if(rotated==NULL){
        return;
    }

    //allocate memory for each row
    for(i=0;i<size;i++){
        rotated[i] = (int*)malloc(size*sizeof(int));
        //check for memory allocation failure
        if(rotated[i]==NULL){
            return;
        }
    }
    //rotate logic
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            rotated[j][size-1-i] = matrix[i][j];
        }
    }

    //copy rotated matrix back to original matrix
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
           matrix[i][j]=rotated[i][j];
        }  
    }

    //free allocated memory
    for(i=0;i<size;i++){
        free(rotated[i]);
    }   
    free(rotated);
}

//the second solution:
//(suppose the matrix has been allocated properly)
// Time Complexity: O(N^2)
// Space Complexity: O(1) - In-place rotation (Optimal)
void rotate_matrix_2(int** matrix,int size){
    int i,j;
    //transpose the matrix
    for(i=0;i<size;i++){
        for(j=i+1;j<size;j++){
            int temp=matrix[i][j];
            matrix[i][j]=matrix[j][i];
            matrix[j][i]=temp;

        }
    }

    //reverse each row
    for(i=0;i<size;i++){
        int left=0,right=size-1;
        while(left<right){
            int temp=matrix[i][left];
            matrix[i][left++]=matrix[i][right];
            matrix[i][right--]=temp;
        }
    }
}