/*
 * 使用说明 / Usage:
 * 1. 编译 / Compile: gcc test1.c -o test1
 * 2. 运行 / Run:     test1 10 20
 *    (在 Windows PowerShell 中可能需要输入: .\test1.exe 10 20)
 * 3. 结果 / Result:  Sum: 30
 */
#include <stdio.h> 
#include <stdlib.h>
int main(int argc, char *argv[ ]){ 
    int k;
    // for(k = 1; k < argc; k++) /* 从第1个命令行参数开始 */
    //     printf("%s ", argv[k]); /* 打印命令行参数 */
    printf("\n");

    // [分析] 安全检查：防止因参数不足导致访问 argv[1] 或 argv[2] 时发生段错误
    if (argc < 3) {
        printf("Error: Please provide two integers as arguments.\n");
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }

    int a= atoi(argv[1]);
    int b= atoi(argv[2]);
    printf("Sum: %d\n", a + b);
    return 0;
}
