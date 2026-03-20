#include<stdio.h>
int main(){
    int n, i, j, k, count = 0;
    scanf("%d", &n);
    for(i = 1; i <= n / 5; i++){
        int remain = n - 5 * i;  // 计算5分硬币后剩余的金额，减少重复计算
        for(j = 1; j <= remain / 2; j++){  // 用remain简化条件
            k = remain - 2 * j;  // 等价于n - 5*i - 2*j，更简洁
            if(k >= 0){  // 若要求1分至少1枚，改为k >= 1
                count++;
                // 直接计算总数量，无需total变量
                printf("fen5:%d, fen2:%d, fen1:%d, total:%d\n", i, j, k, i + j + k);
            }
        }
    }
    printf("count = %d", count);  // 确保格式正确
    return 0;
}