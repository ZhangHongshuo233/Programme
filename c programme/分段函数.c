#include <stdio.h>
#include <math.h>

int main() {
    double x, result;
    // 输入实数x
    scanf("%lf", &x);

    if (x >= 0) {
        // 当x >= 0时，f(x) = x的0.5次方（即平方根）
        result = sqrt(x);
    } else {
        // 当x < 0时，f(x) = (x + 1)的平方 + 2x + 1/x
        result = pow(x + 1, 2) + 2 * x + 1 / x;
    }

    // 按格式输出，x和result都保留两位小数
    printf("f(%.2f) = %.2f\n", x, result);

    return 0;
}
