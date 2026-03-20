#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    int count=0,flag=0;
    while((ch=getchar())!='\n'){
        if(ch==' ') {
            if(count!=0){
                printf("%d ",count);
                count=0;
                flag++;
            } 
            
        }else{
            count++;
        }}
    if(count!=0)
        printf("%d ",count);
    if(flag==0)
        printf("%d",flag);

    
    return 0;
}
