#include <stdio.h>
#include <string.h>  // 包含字符串操作函数库

int main() {
    int n;
    char smin[100];  // 存储最小字符串
    char s[100];     // 临时存储输入的字符串

    // 读入字符串个数
    scanf("%d", &n);
    // 读入第一个字符串，初始化最小字符串
    scanf("%s", smin);  
    // 依次读入剩余字符串并比较
    for (int i = 1; i < n; i++) {
        scanf("%s", s);
        // 使用strcmp比较字符串大小
        if (strcmp(s, smin) < 0) {
            strcpy(smin, s);  // 更新最小字符串
        }
    }  
    // 输出结果
    printf("min is %s\n", smin);

    return 0;
}