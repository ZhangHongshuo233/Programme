#include<stdio.h>
#include<string.h>
int main(){


// 输入一个以#结束的字符串，本题要求滤去所有的非十六进制字符（不分大小写），组成一个新的表示十六进制数字的字符串，然后将其转换为十进制数后输出。如果在第一个十六进制字符之前存在字符“-”，则代表该数是负数。

// 输入格式：
// 输入在一行中给出一个以#结束的非空字符串。

// 输出格式：
// 在一行中输出转换后的十进制数。题目保证输出在长整型范围内。
    char str[81];
    fgets(str,81,stdin);
    str[strcspn(str,"#")]='\0';

    int idx=0;
    char result[81];
    int has_minus=0;
    for(int i=0;i<strlen(str);i++){
        char ch=str[i];
        //第一个字符如果是'-'，保留
        if(str[i]=='-' && idx==0 && !has_minus){
            has_minus=1;
            result[idx++]=str[i];
        }
        //保留十六进制字符
        else if(ch>='0'&&ch<='9' || ch>='a'&&ch<='f' ||ch>='A'&&ch<='F'){
            result[idx++]=ch;
        }
    }
    result[idx]='\0';

    //处理特殊情况
    if(idx==0||idx==1&&result[0]=='0'){  
        printf("0\n");
        return 0;
    }
     
    long long dicimal;
    sscanf(result,"%llx",&dicimal);
    printf("%lld\n",dicimal);
 



    return 0;
} 