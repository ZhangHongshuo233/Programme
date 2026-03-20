/*
题目：
给定两个整型数组，本题要求找出不是两者共有的元素。

输入格式:
输入分别在两行中给出两个整型数组，每行先给出正整数N（≤20），
随后是N个整数，其间以空格分隔。 

输出格式:
在一行中按照数字给出的顺序输出不是两数组共有的元素，数字间以空格分隔，
但行末不得有多余的空格。题目保证至少存在一个这样的数字。同一数字不重复输出。
*/
#include<stdio.h>
int is_in_array(int a[],int x,int size){
    int i;
    for(i=0;i<size;i++){
        if(a[i]==x){
            return 1;
        }
    }
    return 0;
}
int main(){
    int n,m,i,j;
    scanf("%d",&n);
    int a[n];
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    scanf("%d",&m);
    int b[m];
    for(i=0;i<m;i++){
        scanf("%d",&b[i]);
    }
    int c[n+m];
    int count=0;

    for(i=0;i<n;i++){
        if(!is_in_array(b,a[i],m)){
            if(!is_in_array(c,a[i],count)){
                c[count++]=a[i];
            }

        }
    }
    for(i=0;i<m;i++){
        if(!is_in_array(a,b[i],n)){
            if(!is_in_array(c,b[i],count)){
                c[count++]=b[i];
            }
        }
    }

    for(i=0;i<count;i++){
        if(i==0){
            printf("%d",c[i]);
            continue;
        }else{
            printf(" %d",c[i]);
        }
    }
    return 0;

}