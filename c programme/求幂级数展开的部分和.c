#include <stdio.h>
#include <math.h>

int main() {
    double x, sum, term;
    int k;
    
    scanf("%lf", &x);
    
    sum = 1.0;  // 第一项为 1
    term = 1.0; // 当前项，初始为 1
    
    // 计算幂级数，直到某一项的绝对值小于 0.00001
    for (k = 1; ; k++) {
        // 计算第 k 项：x^k / k!
        // 递推关系：term(k) = term(k-1) * x / k
        term = term * x / k;
        
        // 累加当前项
        sum += term;
        
        // 如果当前项的绝对值小于 0.00001，停止
        if (fabs(term) < 0.00001) {
            break;
        }
    }
    
    /*也可以写成
    while(fabs(term) < 0.00001){
        term = term * x / k;
        sum += term;
        k++;
    }
    sum+=term;  //加上最后一项
    */
    printf("%.4lf\n", sum);
    return 0;
}