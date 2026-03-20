#include <stdio.h>

#pragma pack(8)   
struct Test {
    char a;
    double e;
    int b;
    char c;
    double d;  
};
#pragma pack()    // 关闭自定义对齐，恢复编译器默认对齐规则

int main(){
    printf("Size of struct Test: %zu\n", sizeof(struct Test));  //输出Size of struct Test: 32

    return 0;
}