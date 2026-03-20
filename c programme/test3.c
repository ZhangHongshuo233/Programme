#include <stdio.h>
#include<errno.h>
#include <string.h>
#include <stdlib.h>
// 自定义结构体（二进制数据示例）
typedef struct {
    int id;
    char name[20];
    float score;
} Student;

int main(){
    Student a={ 2,"LiSi",88.0};
    FILE *fp=fopen("student2.bin","wb");
    if(fp==NULL){
        perror("fopen failed\n");
        exit(1);
    }
    fwrite(&a,sizeof(Student),1,fp);
    fclose(fp);

    Student b;
    fp=fopen("student.bin","rb");  
    if(fp==NULL){
        perror("fopen failed\n");
        exit(1); 
    }
    fread(&b,sizeof(Student),1,fp);
    printf("ID:%d, 姓名:%s, 分数:%.1f\n", b.id, b.name, b.score);
    fclose(fp);
    fp=NULL;
    return 0;
}