#define MAXS 1000
#include<stdio.h>
char *match(char *s, char ch1, char ch2) {
    static char result[MAXS * 3];  // 足够大以容纳两行结果
    char *p1 = NULL;
    char *p2 = NULL;
    int idx = 0;
    
    // 查找ch1第一次出现的位置
    for (char *p = s; *p != '\0'; p++) {
        if (*p == ch1) {
            p1 = p;
            break;
        }
    }
    
    // 如果没找到ch1，返回空行+换行+空行
    if (p1 == NULL) {
        result[0] = '\n';
        result[1] = '\0';
        return result;
    }
    
    // 从ch1位置查找ch2
    for (char *p = p1; *p != '\0'; p++) {
        if (*p == ch2) {
            p2 = p;
            break;
        }
    }
    
    // 第一行：从ch1到ch2（如果找到ch2）或到字符串末尾（如果没找到ch2）
    if (p2 != NULL) {
        // 找到了ch2，输出ch1到ch2
        for (char *p = p1; p <= p2; p++) {
            result[idx++] = *p;
        }
    } else {
        // 没找到ch2，输出ch1到字符串末尾
        for (char *p = p1; *p != '\0'; p++) {
            result[idx++] = *p;
        }
    }
    
    // 添加换行符
    result[idx++] = '\n';
    
    // 第二行：从ch1到字符串末尾
    for (char *p = p1; *p != '\0'; p++) {
        result[idx++] = *p;
    }
    
    result[idx] = '\0';
    
    return result;
}