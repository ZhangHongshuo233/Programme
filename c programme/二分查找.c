#include <stdio.h>
#define MAXN 10

int main()
{
    int found, i, left, mid, n, right, sorted, x;
    int a[MAXN];

    scanf("%d %d", &n, &x);
    for(i = 0; i < n; i++){
        scanf("%d", &a[i]);
    }

    sorted = 1;
    for(i = 1; i < n; i++){
        if(a[i] < a[i-1] || a[i] == a[i-1]){
            sorted = 0;
            break;
        }
    }
    if(sorted == 0){
        printf("Invalid Value\n");
    }else{
        found = 0;
        left = 0;
        right = n - 1;
        while(left <= right){
            mid = (left + right) / 2;
            if (x == a[mid]){
                found = 1;
                break;
            }else if (x < a[mid]){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }
        if(found != 0){
            printf("%d\n",mid);
        }else{
            printf("Not Found\n");
        }
    }

    return 0;
}
//解析：首先检查数组是否为从小到大且无重复（若存在逆序或重复则输出Invalid Value）。
//若数组合法，通过二分查找（不断缩小左右边界）查找目标值x，找到则输出下标，否则输出Not Found。