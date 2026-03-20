#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    char str[1000];
    fgets(str,1000,stdin);
    str[strcspn(str,"\n")]='\0';
    char* p=str;
    while(*p==' '&&*p!='\0'){
        p++;
    }
    if(*p=='\0'){
        printf("0 ");
    }else{
        while(*p!='\0'){
            if(*p!=' '){
                int len=0;
                while(*p!=' '&&*p!='\0'){
                    len++;
                    p++;
                }
                printf("%d ",len);
                while(*p==' '&&*p!='\0'){
                    p++;
                }   
            }
        }
    }
    return 0;
}