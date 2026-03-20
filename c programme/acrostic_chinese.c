//本题要求编写一个解密藏头诗的程序。

//注：在 2022 年 7 月 14 日 16 点 50 分以后，该题数据修改为 UTF-8 编码。

//输入格式：
//输入为一首中文藏头诗，一共四句，每句一行。注意：一个汉字占三个字节。

//输出格式：
//取出每句的第一个汉字并连接在一起形成一个字符串并输出。同时在末尾输入一个换行符。

#include<stdio.h>
#include<string.h>
int main(){
    char str[4][100];
    for(int i=0;i<4;i++){
        fgets(str[i],100,stdin);
    }
    char result[14];
    for(int i=0;i<4;i++){
        result[i*3]=str[i][0];
        result[i*3+1]=str[i][1];
        result[i*3+2]=str[i][2];
    }
    result[12]='\n';
    result[13]='\0';
    printf("%s",result);
    return 0;
}