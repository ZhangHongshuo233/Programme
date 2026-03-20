#include<stdio.h>
#include<errno.h>
#include <string.h>
#include <stdlib.h>
void encrypt(char *pwd){
    int i=0;
    for(i=0;i<strlen(pwd);i++){
        pwd[i]=pwd[i]^15;
    }
}

typedef struct{
    char username[50];
    char pwd[50];
}user;

int main(){
    user user;
    FILE* fp;
    fp=fopen("f122.dat","w");
    if(fp==NULL){
        perror("fopen failed");
        exit(1);
    }
    
    for(int i=0;i<5;i++){
        scanf("%s %s",user.username,user.pwd);
        encrypt(user.pwd);
        fprintf(fp,"%s %s\n",user.username,user.pwd);
    }
    if(fclose(fp)!=0){
        perror("fclose failed");
        exit(1);
    }
    fp=NULL;
    return 0;
}  