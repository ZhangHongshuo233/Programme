#include <stdio.h>

int main() {
    int n, i, j;
    char ch = 'A';  // 从字母A开始
    
    scanf("%d", &n);
    
    // 外层循环控制行数
    for (i = 1; i <= n; i++) {
        // 内层循环控制每行的字母个数
        // 第1行输出n个，第2行输出n-1个，...，第n行输出1个
        for (j = 1; j <= n - i + 1; j++) {
            printf("%c ", ch);
            ch++;  // 字母递增
        }
        printf("\n");  // 换行
    }
    
    return 0;
}