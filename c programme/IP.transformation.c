#include<stdio.h>
#include<string.h>
int main(){
    // Read a string of 32 characters
    char str[33]; 
    scanf("%s",str);
    int i,j;
    // Split the string into four substrings of 8 characters each
    for(i=0;i<4;i++){
        char temp[9];
        strncpy(temp,str+i*8,8);
        temp[8]='\0';
        int decimal=0;
        // Convert each substring from binary to decimal
        for(j=7;j>=0;j--){
            decimal=decimal*2+(temp[j]-'0');
        }
        if(i==0)
        printf("%d",decimal);
        else
        printf(".%d",decimal);
    }
}