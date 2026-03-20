  #include<stdio.h>
//插入排序函数:对数组arr进行插入排序，数组长度为n
void insertionSort(int arr[],int n){
    int i,j,key;

    //遍历数组，i是“未排序部分”的起始索引
    for(i=1;i<n;i++){ 
        //从数组第二个元素开始遍历(数组第一个元素默认已排序)
        key=arr[i];     //取出“未排序部分”的第一个元素作为待插入的值（key）
        j=i-1;          // j指向“已排序部分”的最后一个元素（初始为i-1，即已排序部分的末尾）

        //当j未越界（>=0），且“已排序部分”的元素a[j]大于key时，将a[j]后移一位
        while(j>=0 && arr[j]>key){
            arr[j+1]=arr[j];//元素后移，为key腾出位置
            j--;            //继续向前比较
        }
        arr[j+1]=key;       //将key插入到正确位置（j+1是退出循环后找到的插入索引）
    }
}
  
int main() {
    int n, i;
    printf("请输入数组长度：");
    scanf("%d", &n); 

    int arr[n];  // 定义长度为n的数组（C99支持变长数组）
    printf("请输入%d个整数：", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 调用插入排序函数
    insertionSort(arr, n);
 
    // 输出排序后的数组
    printf("排序后的数组：");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
//解析：插入排序通过将“未排序部分”的第一个元素插入到“已排序部分”的正确位置来实现排序。 
//外层循环遍历数组，内层循环找到插入位置并移动元素。最后将key插入正确位置。
//主函数中读入数组长度和元素，调用插入排序函数，并输出排序结果。       