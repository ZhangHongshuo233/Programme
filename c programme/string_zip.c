#include <stdio.h>
#define MAXN 99
void zip(char*p){
    int n ;
    char*q=p;
    while(*p!='\0'){
        n=1;
        while(*p==*(p+n)&& *(p+n) != '\0' ){
            n++;
        }
        if(n>=10){
            *q++=(n/10)+'0';
            *q++=(n%10)+'0';
        }
        else if (n>=2){
            *q++=n+'0';
        }
        *q++=*(p+n-1);
        p=p+n;
    }
    *q='\0';
}
// 测试示例
int main() {
    char str[MAXN];
    printf("请输入字符串：");
    fgets(str, MAXN, stdin);  // 安全读取输入
    // 移除fgets可能带入的换行符
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
    zip(str);
    printf("压缩后：%s\n", str);
    return 0;
}