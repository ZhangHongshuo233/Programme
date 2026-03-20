#include<stdio.h>
void right_rotate(int a[],int n,int m){
    int i,j,temp;
    for(i=0;i<m;i++){
        temp=a[n-1];
        for(j=n-1;j>0;j--){
            a[j]=a[j-1];
        }
        a[0]=temp;
    }
}
int main(){
    int n,m,i;
    //读入数组元素个数及元素值
    scanf("%d %d",&n,&m);
    int a[n];
    for(i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    right_rotate(a,n,m);
    //输出旋转后的数组元素，确保行末无多余空格
    for(i=0;i<n;i++){
        if(i==0){
            printf("%d",a[i]);
        }else{
            printf(" %d",a[i]);
        }
    }
}

//实际上我们可以用"三次反转法"来实现数组的右旋转，时间复杂度为O(n)，空间复杂度为O(1)。
//具体做法是：
//1. 反转整个数组
//2. 反转前m个元素  
//3. 反转后n-m个元素
//这样就能实现数组的右旋转。
// void reverse(int a[], int left, int right) {
//     // 反转数组 a 中 [left, right] 区间的元素
//     while (left < right) {
//         int temp = a[left];
//         a[left++] = a[right];
//         a[right--] = temp;
//     }
// }

// void right_rotate(int a[], int n, int m) {
//     int k = m % n;  // 实际有效旋转次数
//     if (k == 0) return;  // 无需旋转
//     reverse(a, 0, n-1);    // 反转整个数组
//     reverse(a, 0, k-1);    // 反转前 k 个元素
//     reverse(a, k, n-1);    // 反转后 n-k 个元素
// }