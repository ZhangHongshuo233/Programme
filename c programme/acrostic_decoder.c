//编写程序，输出一首英文藏头诗的真实含义。输入的藏头
//诗小于20行，每行不超过80个字符，以#作为输入结束标志，使用动态内存分配方法处理字符串的输入。
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    int i=0,j;
    char *poem[20],str[80],mean[20];
    fgets(str,80,stdin);
    str[strcspn(str,"\n")]='\0';
    while(strcmp(str,"#")!=0){
        poem[i]=(char*)malloc((strlen(str)+1)*sizeof(char));
        strcpy(poem[i],str);
        i++;
        fgets(str,80,stdin);
        str[strcspn(str,"\n")]=0;
    }
    for(j=0;j<i;j++){
        mean[j]=poem[j][0];
        free(poem[j]);
    }
    mean[i]='\0';
    puts(mean);
    return 0;   
}
