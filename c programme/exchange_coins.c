// 将一笔零钱换成5分、2分和1分的硬币，要求每种硬币至少有一枚，有几种不同的换法？

// 输入格式:
// 输入在一行中给出待换的零钱数额x∈(8,100)。

// 输出格式:
// 要求按5分、2分和1分硬币的数量依次从大到小的顺序，输出各种换法。每行输出一种换法，格式为：“fen5:5分硬币数量, fen2:2分硬币数量, fen1:1分硬币数量, total:硬币总数量”。最后一行输出“count = 换法个数”。


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){

    int n;
    int cnt=0;
    scanf("%d",&n);
    for(int i=(n-3)/5;i>0;i--){
        for(int j=(n-i*5-1)/2;j>0;j--){
            int k=n-i*5-j*2;
            if(k!=0){
                cnt++;
                printf("fen5:%d, fen2:%d, fen1:%d, total:%d\n",i,j,k,i+j+k);
            }else{
                break;
            }
        }
    }
    printf("count = %d",cnt);
    



    return 0;
}