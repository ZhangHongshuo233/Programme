// 
// void strmcpy( char *t, int m, char *s ){
//     //计算字符串长度
//     int len=0;
//     while(*(t+len)!='\0'){
//         len++;
//     }
//     //
//     if(m<=0||m>len){
//         *s='\0';
//         return;
//     }else{
//         t=t+m-1;
//         while(*t!='\0'){
//             *(s++)=*(t++);
//         }  
//     *s='\0'; 
//     }
// }

// int max(int*a,int m,int n){
//     if(m==n){
//         return a[m];
//     }else{
//         int k=m+(n-m)/2;
//         int u,v;
//         u=max(a,m,k);
//         v=max(a,k+1,n);
//         return u>v?u:v;

//     }
// }

// 
#include <stdio.h>
#include <string.h>
void fsort(const char *color[ ], int n);
int main(void)
{
    int i, flag = 0;
    char ch;
    const char *color[5] = {"red", "blue", "yellow", "green", "black" };
    // printf("Input a letter: ");
    // ch = getchar();
    for(i = 0; i < 5; i++) {
        
    //     if(*color[i] == ch){
    //         flag = 1;
    //         puts(color[i]);
    //     }
    // }
    // if(flag == 0) {
    //     printf("Not Found\n"); 

        printf ("%s %x\n", color[i], color[i]);

    }

    // const char **pc; 
    // pc = color; 
    // printf("Input a letter:");
    // ch = getchar();
    // for(i = 0; i < 5; i++) {
    //     if(**(pc + i) == ch){
    //         flag = 1;
    //         puts( *(pc + i) );
    //     }
    // }

    // ch = getchar();
    // char*pcolor[5]= {"red", "blue", "yellow", "green", "black" };
    // for(i=0;i<5;i++){
    //     if(*pcolor[i]==ch){
    //         flag=1;
    //         puts(pcolor[i]);
    //     }
    // }

    fsort(color,5);
    for(i = 0; i < 5; i++) {
        printf ("%s\n", color[i]);
    }

    return 0;
}
void fsort(const char *color[ ], int n){
    int i,j;
    const char*temp;
    for(i=0;i<n-1;i++){
        for(j=0;j<n-1-i;j++){
            if(strcmp(color[j],color[j+1])>0){
                temp=color[j];
                color[j]=color[j+1];
                color[j+1]=temp;
            }
        }
   }
} 