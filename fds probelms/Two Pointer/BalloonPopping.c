#include <stdio.h>
#include <stdlib.h>
// Balloon Popping Problem
// Given n balloons with their heights and a maximum height difference h, find the position to pop the maximum number of balloons and the count of those balloons.
// Input:
// The first line contains two integers n and h, where n is the number of balloons and
// h is the maximum height difference allowed.
// The second line contains n integers representing the heights of the balloons.
// Output:
// Print two integers: the position to pop the balloons and the count of those balloons.
//方法：滑动窗口(双指针)
//时间复杂度：O(n)

int main() {
    int n,h;
    scanf("%d %d",&n,&h);

    int a[n];
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }

    int pos=0,max=0;
      
    int left=0;
    for(int right=0;right<n;right++){
        while(a[right]-a[left]>h){
            left++;
        }
        int cnt=right-left+1;
        int coord=a[right]-h;
        if(cnt>max){
            max=cnt;
            pos=coord;
        }else if(cnt==max){
            if(coord<pos){
                pos=coord;
            }
        }
    }
    printf("%d %d\n",pos,max);
    return 0;
}