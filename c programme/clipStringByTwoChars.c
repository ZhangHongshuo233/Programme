//裁判程序
#include <stdio.h>
#define MAXS 10

char *clipStringByTwoChars( char *input_str, char start_char, char end_char );

int main(){
    char str[MAXS], ch_start, ch_end, *p;
    
    scanf("%s\n", str);
    scanf("%c %c", &ch_start, &ch_end);
    p = clipStringByTwoChars(str, ch_start, ch_end);
    printf("%s\n", p);

    return 0;
}

#include <string.h>
char *clipStringByTwoChars( char *input_str, char start_char, char end_char ){
    char* start_ptr=NULL,*end_ptr;
    // 查找start_char和end_char在字符串s中的位置(这种方法有缺陷，无法处理未找到字符的情况)
    // start_ptr=input_str+strcspn(input_str,(char[]){start_char,'\0'});
    end_ptr=input_str+strcspn(input_str,(char[]){end_char,'\0'});//因为strcspn的参数是字符串，所以这里用字符数组来覆盖单字符

    //PS:也可以调用strchr函数（有缺陷，无法处理未找到字符的情况）
    // start_ptr=strchr(input_str,start_char);
    // end_ptr=strchr(input_str,end_char);

    //或者不调用库函数，自己遍历查找
    for(char*p=input_str;*p!='\0';p++){
        if(*p==start_char){
            start_ptr=p;
            break;
        }
        // if(*p==end_char){
        //     end_ptr=p;
        //     break;
        // }
    }

    // 如果没有找到start_char，返回空字符串
    if(start_ptr==NULL){
        return "\n";
    }
    static char result[MAXS*3]; // 足够大以容纳两行结果
    int len=0;
    // 第一行：从start_char到end_char（如果找到end_char）或到字符串末尾（如果没找到end_char）
    for(char* p=start_ptr;p<=end_ptr&&*p!='\0';p++){
        result[len++]=*p;
    }
    // 添加换行符
    result[len++]='\n';
    result[len]='\0';
    // 第二行：从start_char到字符串末尾
    strcat(result,start_ptr);
    return result;
}




