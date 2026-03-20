#include<stdio.h>
int main() {
    // 打开文件（只写模式，不存在则创建，存在则清空）
    FILE *fp = fopen("output.txt", "w");

    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }

    // 写入内容
    fprintf(fp, "Hello, fopen!\n");
    fprintf(fp, "数字：%d,浮点数：%.2f\n", 100, 3.14);

    // 关闭文件
    fclose(fp);
    fp = NULL;
    return 0;
}

// int main() {
//     // 打开文件（只读模式）
//     FILE *fp = fopen("test.txt", "r");
//     if (fp == NULL) {  // 必须检查打开是否成功
//         perror("fopen failed");  // 打印错误原因（如文件不存在）
//         return 1;
//     }

//     // 读取文件内容（示例：逐行读取）
//     char buf[1024];
//     while (fgets(buf, sizeof(buf), fp) != NULL) {
//         printf("读取内容：%s", buf);
//     }

//     // 关闭文件（必须！）
//     fclose(fp);
//     fp = NULL;  // 清空指针，避免野指针
//     return 0;
// }