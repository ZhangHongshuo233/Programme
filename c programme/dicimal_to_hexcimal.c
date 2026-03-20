void reverse(char a[],int n){
    int left=0,right=n-1;
    while(left<right){
        char temp;
        temp=a[left];
        a[left]=a[right];
        a[right]=temp;
        left++;
        right--;
    }
}
void Shift( char s[] ){ 
        void(*fp)(char a[],int n)=&reverse;
    
        int m=strlen(s);
        if (m < 3) return; // 防止字符串过短导致越界
        (*fp)(s,m);
        (*fp)(s,m-3);
        (*fp)(s+m-3,3);
}
void f( long int x, char *p ){
    int digit=0,hex;
    unsigned long temp;

    // 处理 0 的特殊情况
    if (x == 0) {
        p[0] = '0';
        p[1] = '\0';
        return;
    }

    // 处理负数，取绝对值
    if (x < 0) {
        temp = -(unsigned long)x;
    } else {
        temp = (unsigned long)x;
    }

    unsigned long val = temp; // 备份绝对值

    //确定十六进制位数
    while(temp!=0){
        temp/=16;
        digit++;
    }
    
    if (x < 0) {
        digit++; // 为负号预留位置
    }

    p[digit] = '\0'; // 添加字符串结束符
    
    temp = val;
    while(temp!=0){
        hex=temp%16;
        temp/=16;
        digit--; // 修正：从后往前填充，先减小下标
        if(hex>=0&&hex<=9){
            p[digit]=hex+'0';
        }else{
            switch(hex){
                case 10:p[digit]='A';break;
                case 11:p[digit]='B';break;
                case 12:p[digit]='C';break;
                case 13:p[digit]='D';break;
                case 14:p[digit]='E';break;
                case 15:p[digit]='F';break;
            }
        }
    }

    if (x < 0) {
        p[0] = '-';
    }
}