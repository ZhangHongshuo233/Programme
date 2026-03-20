#include <stdio.h>
int main() {
    int N, i, num;
    int count[10] = {0};  
    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &num);
        if (num == 0) {
            count[0]++;
            continue;
    }
        while (num > 0) {
            int digit = num % 10;  
            count[digit]++;
            num /= 10;  
        }
    }
    int M = 0;
    for (i = 0; i < 10; i++) {
        if (count[i] > M) {
            M = count[i];
        }
    }
    printf("%d:", M);
    for(i=0;i<10;i++){
        if(count[i]==M){
            printf(" %d",i);
        }
    }
    printf("\n");

// //另一种输出方式
// int result[10], len = 0;
//     for (i = 0; i < 10; i++) {
//         if (count[i] == M) {
//             result[len++] = i;
//         }
//     }
//     printf("%d:", M);
//     for (i = 0; i < len; i++) {
//         printf(" %d", result[i]);
//     }
//     printf("\n");

    return 0;
}