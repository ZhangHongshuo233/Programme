// 已知文件 c:/temp/data.txt 中的数据为若干个实数（每个实数的字符长度不超过 20），例如：1e-2、.115、0.050 等，所有实数之间仅用空格间隔。
// 要求编写 C 语言程序完成以下功能：
// 1.从该文件中读取所有实数；
// 2.必须定义指定结构体：struct item { char s[20]; double v; };
// 3.使用while循环统计文件中的实数总个数count；
// 4.使用动态内存分配：struct item *p=(struct item*)malloc(count*sizeof(struct item));
// 5.读取数据时，必须严格按顺序使用以下三行固定语句：
//     fscanf(fp,"%s",p[i].s);
//     fseek(fp, ?, SEEK_CUR);
//     fscanf(fp,"%lf",&p[i].v);
// 6.采用冒泡排序法对读取的所有实数，按照数值从小到大的规则排序；
// 7.最终输出排序后的结果，必须严格按照原文件中的实数格式输出；
// 8.完成所有操作后释放动态分配的内存，文件操作需做判空处理。

// code:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct item {
    char s[20];
    double v;
};
int main() {
    FILE *fp = fopen("exam.data.txt", "r");
    if (fp == NULL) {
        printf("Failed to open file.\n");
        exit (1);
    }

    int count = 0;
    char temp[20];
    while (fscanf(fp, "%s", temp) == 1) {
        count++;
    }

    struct item *p = (struct item *)malloc(count * sizeof(struct item));
    if (p == NULL) {
        printf("Memory allocation failed.\n");
        fclose(fp);
        exit (1);
    }

    fseek(fp, 0, SEEK_SET);
    for (int i = 0; i < count; i++) {
        fscanf(fp, "%s", p[i].s);
        fseek(fp, -(long)strlen(p[i].s)  , SEEK_CUR);
        fscanf(fp, "%lf", &p[i].v);
    }

    // Bubble sort
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (p[j].v > p[j + 1].v) {
                struct item swap_temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = swap_temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        puts(p[i].s);
        if (i != count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    free(p);
    fclose(fp);
    return 0;
}