  
// 本题要求统计一个整型序列中出现次数最多的整数及其出现次数。

// 输入格式：
// 输入在一行中给出序列中整数个数N（0<N≤1000），以及N个整数。数字间以空格分隔。

// 输出格式：
// 在一行中输出出现次数最多的整数及其出现次数，数字间以空格分隔。题目保证这样的数字是唯一的。
#include <stdio.h>
int main( ){  

    int n;
    scanf("%d",&n);
    int a[1000];
    int val[1000];
    int cnt[1000]={0};
    int len=0;
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    // 统计不同数字
    for(int i=0;i<n;i++){
        int found=0;
        for(int j=0;j<len;j++){
            if(a[j]==a[i]){
                found=1;
            }
        }
        if(!found){
            val[len]=a[i];
            len++;
        }
    }

    // 统计出现次数
    for(int i=0;i<n;i++){
        for(int j=0;j<len;j++){
            if(a[i]==val[j]){
                cnt[j]++;
            }
        }
    }

    // 找出出现次数最多的数字
    int max=0;
    for(int i=1;i<len;i++){
        if(cnt[i]>cnt[max]){
            max=i;
        }
    }

    // 输出结果
    printf("%d %d",val[max],cnt[max]);
    return 0;
}