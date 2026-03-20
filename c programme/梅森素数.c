#include <stdio.h>

// 判断一个数是否为素数
int isPrime(long num) {
    int i;
    if (num < 2) return 0;
    if (num == 2) return 1;
    if (num % 2 == 0) return 0;
    
    for (i = 3; i * i <= num; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int n, i, j;
    long limit, mersenne;
    int found = 0;
    
    scanf("%d", &n);
    
    // 计算上限 2^n - 1
    limit = 1;
    for (i = 0; i < n; i++) {
        limit *= 2;
    }
    limit -= 1;
    
    // 遍历所有素数 p，计算 2^p - 1
    for (i = 2; i <= n; i++) {
        // 首先 i 必须是素数
        if (!isPrime(i)) continue;
        
        // 计算 2^i - 1
        mersenne = 1;
        for (j = 0; j < i; j++) {
            mersenne *= 2;
        }
        mersenne -= 1;
        
        // 如果超过上限，停止
        if (mersenne > limit) {
            break;
        }
        
        // 判断 2^i - 1 是否为素数
        if (isPrime(mersenne)) {
            printf("%ld\n", mersenne);
            found = 1;
        }
    }
    
    // 如果没有找到，输出 None
    if (!found) {
        printf("None\n");
    }
    
    return 0;
}