#include <stdio.h>

int main() {
    char ch;
    int i;

    printf("Enter 8 characters: ");

    for (i = 1; i <= 8; i++) {
        // 读取字符，若遇到空白符则重新读取
        ch = getchar();
        while (ch == ' ' || ch == '\n' || ch == '\t') {
            ch = getchar(); // 跳过空格、换行、制表符
        }

        putchar(ch); // 输出有效字符
        if (i < 8) {
            putchar('-'); // 前7个字符后加"-"，第8个不加
        }
    }

    putchar('\n');
    return 0;
}
