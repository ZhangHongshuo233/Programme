#include <stdio.h>

int main() {
    long n;
    long divisor = 1;
    long temp;
    
    scanf("%ld", &n);
    
    // 处理负数
    if (n < 0) {
        n = -n;
    }
    
    // 特殊情况：n为0
    if (n == 0) {
        printf("0 \n");
        return 0;
    }
    
    // 找到最高位的除数
    temp = n;
    while (temp >= 10) {
        divisor *= 10;
        temp /= 10;
    }
    
    // 从高位到低位逐位输出
    while (divisor > 0) {
        printf("%ld ", n / divisor);
        n %= divisor;
        divisor /= 10;
    }
    printf("\n");
    
    return 0;
}