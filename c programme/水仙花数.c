#include<stdio.h>

// 自定义整数幂计算函数，避免pow的精度问题
int int_pow(int base, int exp) {
    int result = 1;
    for (int k = 0; k < exp; k++) {
        result *= base;
    }
    return result;
}
// 判断一个数是否为水仙花数
int isperfect(int i, int n) {
    int sum = 0;
    int temp = i;
    // 循环n次，提取每位数字
    for (int j = 0; j < n; j++) {  // 从0开始计数更清晰
        int t = temp % 10;
        sum += int_pow(t, n);  // 使用自定义整数幂函数
        temp /= 10;
    }
    return (sum == i) ? 1 : 0;// 返回1表示是水仙花数，否则返回0
}

int main() {
    int n;
    scanf("%d", &n);
    // 用整数乘法计算n位数范围，避免pow误差
    int lower = int_pow(10, n - 1);
    int upper = lower * 10 - 1;
// 遍历n位数范围，查找水仙花数
    for (int i = lower; i <= upper; i++) {
        if (isperfect(i, n)) {
            printf("%d\n", i);
        }
    }
    return 0;
}