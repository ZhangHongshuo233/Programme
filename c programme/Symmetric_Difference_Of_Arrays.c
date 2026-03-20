#include <stdio.h>

int main() {
    int i, j;
    
    int lenA,lenB;
     // 读取第一个数组
    scanf("%d", &lenA);
    int a[lenA];
    for (i = 0; i < lenA; i++) {
        scanf("%d", &a[i]);
    }  
    // 读取第二个数组
    scanf("%d", &lenB);
    int b[lenB];
    for (i = 0; i < lenB; i++) {
        scanf("%d", &b[i]);
    }
  
    int inA[lenA], inB[lenB];  // 标记是否在对方数组中出现
    int c[lenA+lenB], cLen = 0;  // 存储a和b的所有元素（去重前）
   
    // 标记a中元素是否在b中出现
    for (i = 0; i < lenA; i++) {
        inA[i] = 1;  // 先标记为“存在于a”
        for (j = 0; j < lenB; j++) {
            if (a[i] == b[j]) {
                inA[i] = 0;  // 若在b中出现，则标记为“共有”
                break;
            }
        }
    }

    // 标记b中元素是否在a中出现
    for (i = 0; i < lenB; i++) {
        inB[i] = 1;  // 先标记为“存在于b”
        for (j = 0; j < lenA; j++) {
            if (b[i] == a[j]) {
                inB[i] = 0;  // 若在a中出现，则标记为“共有”
                break;
            }
        }
    }

    // 将a和b中“非共有”的元素存入c（同时去重）
    for (i = 0; i < lenA; i++) {
        if (inA[i] == 1) {  // a中独有的元素
            // 去重：检查c中是否已有该元素
            int exist = 0;
            for (j = 0; j < cLen; j++) {
                if (c[j] == a[i]) {
                    exist = 1;
                    break;
                }
            }
            if (!exist) {
                c[cLen++] = a[i];
            }
        }
    }

    for (i = 0; i < lenB; i++) {
        if (inB[i] == 1) {  // b中独有的元素
            // 去重
            int exist = 0;
            for (j = 0; j < cLen; j++) {
                if (c[j] == b[i]) {
                    exist = 1;
                    break;
                }
            }
            if (!exist) {
                c[cLen++] = b[i];
            }
        }
    }

    // 输出结果（按顺序，无重复）
    for (i = 0; i < cLen; i++) {
        if (i > 0) printf(" ");
        printf("%d", c[i]);
    }
    printf("\n");

    return 0;
}
    ////去重操作：

    // for(i=0;i<lenA;i++){
    //     if(inA[i]==1){
    //         int exist=0;
    //         for(j=0;j<cLen;j++){
    //             if(c[j]==a[i]){
    //                 exist=1;
    //                 break;
    //             }
    //         }
    //         if(!exist){
    //             c[cLen++]=a[i];
    //         }    
    //     }
    // }