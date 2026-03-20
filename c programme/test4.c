#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 密码加密函数：每个字符ASCII码低四位取反（与15异或）
void encrypt_password(char *password, char *encrypted_pwd) {
    int i = 0;
    while (password[i] != '\0') {
        // 低四位取反（15的二进制是00001111，异或后低四位翻转）
        encrypted_pwd[i] = password[i] ^ 15;
        i++;
    }
    encrypted_pwd[i] = '\0'; // 字符串结束符
}

// 验证账号/密码是否仅包含字母和数字
int is_valid(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (!isalnum(str[i])) { // 非字母/数字则无效
            return 0;
        }
        i++;
    }
    return 1; // 有效返回1
}

int main() {
    FILE *fp;
    char account[50];    // 存储账号（最多49个字符）
    char password[50];   // 存储原始密码
    char encrypted[50];  // 存储加密后的密码
    int i;

    // 打开文件（写入模式，不存在则创建，存在则覆盖）
    fp = fopen("f122.dat", "w");
    if (fp == NULL) {
        printf("文件打开失败！\n");
        return 1; // 异常退出
    }

    // 输入5个用户信息
    printf("请输入5个用户的账号和密码( 仅包含字母和数字）:\n");
    for (i = 0; i < 5; i++) {
        // 循环输入直到账号合法
        do {
            printf("请输入第%d个用户的账号:", i + 1);
            scanf("%s", account);
            if (!is_valid(account)) {
                printf("账号只能包含字母和数字，请重新输入！\n");
            }
        } while (!is_valid(account));

        // 循环输入直到密码合法
        do {
            printf("请输入第%d个用户的密码:", i + 1);
            scanf("%s", password);
            if (!is_valid(password)) {
                printf("密码只能包含字母和数字，请重新输入！\n");
            }
        } while (!is_valid(password));

        // 加密密码
        encrypt_password(password, encrypted);

        // 写入文件：账号 加密密码（换行）
        fprintf(fp, "%s %s\n", account, encrypted);
    }

    // 关闭文件
    fclose(fp);
    printf("\n成功!5个用户信息已写入文件 f122.dat\n");

    return 0;
}