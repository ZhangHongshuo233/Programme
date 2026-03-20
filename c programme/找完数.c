#include <stdio.h>
int isPerfect(int i){
    int sum=0,j;
    for(j=1;j<i;j++){
        if(i%j==0) sum+=j;
        }
    if(sum==i) return 1;
    else return 0;
    }

int main(){
    int i,j,m,n,found=0;
    scanf("%d %d",&m,&n);
    for(i=m;i<=n;i++){
        /*判断是不是完数*/
        if(isPerfect(i)){
            found=1;
            printf("%d = ",i);
            /*输出“完数 = 因子1 + 因子2 + ... + 因子k”*/
            int first = 1;
            for(j=1;j<i;j++)
                if(i%j==0){
                    if(!first) printf(" + ");
                    printf("%d",j);
                    first =0;
                }
            printf("\n");
            }
        }
    
    if(!found) printf("None\n");
    return 0;
}