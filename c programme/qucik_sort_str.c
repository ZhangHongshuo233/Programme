#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LEN 81

int cmp(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int main(){
    int n,i,j;
    scanf("%d",&n);
    getchar();
    char str[n][MAX_LEN];
    for(i=0;i<n;i++){
        scanf("%s",str[i]);
        getchar();
    }
    
    qsort(str, n, sizeof(str[0]), cmp);
    
    for(i=0;i<n;i++){
        puts(str[i]);
    }
return 0;
}
