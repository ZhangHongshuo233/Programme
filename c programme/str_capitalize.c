#include<string.h>
#include<stdio.h>
void shift1(char* str){
    char* p=str;
    while(*p!='\0'){
        if(*p>='a'&&*p<='z'){
            *p=(*p-'a'+1)%26+'A';
        }
        else if(*p>='A'&&*p<='Z'){
            *p=(*p-'A'+1)%26+'a';
        }
        p++;
    }
}

void shift2(char* str){
    char* p=str;
    if(*p>='a'&&*p<='z'){
        *p=*p-'a'+'A';
        
    }
    p++;
    while(*p!='\0'){
        if(*(p-1)==' '){
            if(*p>='a'&&*p<='z'){
                *p=*p-'a'+'A';
            }
        }
        p++;
    }
}

int main(){
    char str[100];
    fgets(str,100,stdin);
    str[strcspn(str,"\n")]='\0';
    shift2(str);
    printf("%s",str);
    return 0;
}