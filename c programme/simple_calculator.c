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

int isdigit(char ch){
    if(ch>='0'&&ch<='9'){
        return 1;
    }else{
        return 0;
    }
}

void shift3(char* str){
    char* p=str;
    long long result=0;
    //initialize the first operation as '+'
    char op='+';
    int error=0;

    //step1:skip the leading spaces
    while(*p==' '){
        p++;
    }

    //step2:the main loop:read number,apply operation,read next operation ,then repeat the process
    while(*p!='\0'){
        //step2-1:read the number
        if(isdigit(*p)){
            long long num=0;
            //read the full number
            while(isdigit(*p)){
                num=num*10+(*p-'0');
                p++;
            }
            //step2-2:apply the previous operation
            switch(op){
                case '+':result+=num;break;
                case '-':result-=num;break;
                case '*':result*=num;break;
                case '/':if(num==0){ error=1; break;} result/=num;break;  
            }

            //step2-3:skip the spaces and read the next operation
            //skip the spaces before the operation
            while(*p==' '){
                p++;
            }
            //read the next operation
            if(*p=='+'||*p=='-'||*p=='*'||*p=='/'){
                op=*p;
                p++;
                //skip the spaces after the operation
                while(*p==' ') p++;
            }else if(*p!='\0'){
                //invalid character
                error=1;
            }
        }else{
            //not digit, invalid input
            error=1;
            break;
        }

        //step3:output the result
        if(error){
            sprintf(str,"%s","ERROR");
        }else{
            sprintf(str,"%lld",result);
        }
    }
}

int main(){
    char str[10000];
    fgets(str,10000,stdin);
    str[strcspn(str,"=")]='\0';
    shift3(str);
    printf("%s",str);
    return 0;
}