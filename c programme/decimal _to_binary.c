#include<stdio.h>
#include<string.h>
//将十进制数字转为二进制字符串
void decimalToBinary(int num, char* binaryStr) {
    int i;
    binaryStr[32] = '\0'; //字符串结束符
    for(i = 31; i >= 0; i--) {
        binaryStr[i] = (num % 2) ? '1' : '0';
        num /= 2;
    }
    char*first=strchr(binaryStr,'1');
    if(first!=NULL){
        strcpy(binaryStr,first);
    }else{
        binaryStr[0]='0';
        binaryStr[1]='\0';
    }
}
int main(){
    int num;
    char binaryStr[33];
    scanf("%d",&num);
    decimalToBinary(num,binaryStr);
    printf("%s\n",binaryStr);
    return 0;
}