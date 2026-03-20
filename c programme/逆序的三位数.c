#include <stdio.h>

int main() {
    // 用getchar逐个读取三位数字的字符形式
    char c1 = getchar();  // 读取百位字符
    char c2 = getchar();  // 读取十位字符
    char c3 = getchar();  // 读取个位字符

    // 逆序输出：先输出个位，再十位，最后百位
    switch(c3){
    	case '0':
    		switch(c2){
    			case '0':
    				putchar(c1);
    				break;
    			default:
    				putchar(c2);
  				    putchar(c1);
  				    break;}
			break;
			
    	default:
    		putchar(c3);
    		putchar(c2);
    		putchar(c1);
    		break;
			}
			putchar('\n');  // 换行

    return 0;
}
    /*另一种方法： 
#include <stdio.h>

int main() {
    int num;
    // 输入一个三位正整数
    scanf("%d", &num);

    // 分离出个位、十位、百位数字
    int digit1 = num % 10;   // 个位
    int digit2 = (num / 10) % 10; // 十位
    int digit3 = num / 100;  // 百位

    // 计算逆序后的数字
    int reversed = digit1 * 100 + digit2 * 10 + digit3;

    // 输出逆序后的数字
    printf("%d\n", reversed);

    return 0;
} 
*/
