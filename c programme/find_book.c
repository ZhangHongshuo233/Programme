#include<stdio.h>
#include<string.h>
#define MAXN 10
struct Book{
    char name[31];
    double price;
};
int main(){
    struct Book books[MAXN];
    int n,i,j;
    //读入图书数量
    scanf("%d",&n);
    getchar();
    //读入每本图书的信息
    for(i=0;i<n;i++){
        fgets(books[i].name,31,stdin);
        books[i].name[strcspn(books[i].name,"\n")]='\0';
        scanf("%lf",&books[i].price);
        getchar();
    }
    //按价格进行排序（冒泡排序）
    for(i=0;i<n-1;i++){
        for(j=0;j<n-i-1;j++){
            if(books[j].price>books[j+1].price){
                struct Book temp=books[j];
                books[j]=books[j+1];
                books[j+1]=temp;
            }
        }
    }
    //输出排序后价格最高和最低的图书信息
    printf("%.2f, %s\n",books[n-1].price,books[n-1].name);
    printf("%.2f, %s\n",books[0].price,books[0].name);
    return 0;
}