    #include<stdio.h>
    #include<string.h>
    #define MAXN 100
    int verify_id_check_digit(char id[]){
        int weight[] = {7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2};
        char check[] = {'1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2'};
        int sum=0;
        int i;
        //计算加权和
        for(i=0;i<17;i++){
            sum+=(id[i]-'0')*weight[i];
        }
        //计算校验位并比较
        return id[17]==check[sum%11]?1:0;
    }

    int is_first17_digits_valid(char id[]){
        int j;
        for (j = 0; j < 17; j++){
            if(id[j] < '0' || id[j] > '9') return 0;
        }
        return 1;
    }

    int main(){
        int i,j,n;
        int has_invalid=0;

        //一、读入身份证号个数
        scanf("%d",&n);
        // 清空输入缓冲区，避免残留字符干扰后续输入
        while (getchar() != '\n');  

        //二、定义二维数组存储身份证号
        char id[MAXN][19];

        //三、逐一输入并验证身份证号输入有效性
        for(i=0;i<n;i++){

            //输入身份证(注意避免id长度超过18，避免后续数组越界)
            scanf("%18s",id[i]);
            
            //增加长度检验
            if(strlen(id[i])!=18){
                //输出无效身份证号
                printf("%s\n",id[i]); 
                //标记存在无效身份证号
                has_invalid++;
                //跳过后续检查
                continue; 
            }
        
            //检查两项：前17位是否有效，第18位校验码是否正确
            if(!is_first17_digits_valid(id[i])||!verify_id_check_digit(id[i])){
                //输出无效身份证号(注意换行符)
                printf("%s\n",id[i]);
                //标记存在无效身份证号
                has_invalid++;
            }
        }

        //如果没有无效身份证号，输出“All passed”
        if(has_invalid==0){
            printf("All passed\n");
        }
        return 0;
    }