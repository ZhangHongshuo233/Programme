#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkstack.h"
 
int temp_num = 0; // 临时存储拼接的多位数
 
// 拼接数字（处理多位数，如"20"由'2'和'0'拼接）
void concat_num(char c)
{
    temp_num = temp_num * 10 + (c - '0');
}
 
// 获取运算符优先级（*、/优先级高于+、-）
int get_priority(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0; // 非法运算符
    }
}
 
// 计算两个数的运算结果
int calc_result(int num1, int num2, char op)
{
    switch (op)
    {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': 
            if (num2 == 0) {
                printf("calc_result: divide by zero\n");
                exit(1);
            }
            return num1 / num2;
        default: return 0;
    }
}
 
int main(int argc, char** argv)
{
    char express[] = "20*3+25/5-8"; // 待计算的中缀表达式
    DATATYPE data = {0};
    // 创建操作数栈和运算符栈
    LinkStack* num_stack = CreateLinkStack();
    LinkStack* op_stack = CreateLinkStack();
    if (num_stack == NULL || op_stack == NULL) {
        printf("main: create stack failed\n");
        return 1;
    }
    
    DATATYPE* top_op = NULL;
    char* tmp = express;
 
    // 遍历表达式
    while (*tmp != '\0')
    {
        memset(&data, 0, sizeof(data));
        // 处理数字（拼接多位数）
        if (*tmp >= '0' && *tmp <= '9')
        {
            concat_num(*tmp);
            tmp++;
            continue;
        }
 
        // 数字入操作数栈
        data.num = temp_num;
        temp_num = 0;
        PushLinkStack(num_stack, &data);
 
        // 处理运算符：按优先级入栈/计算
        top_op = GetTopLinkStack(op_stack);
        while (1)
        {
            // 运算符入栈条件：栈空 或 当前运算符优先级更高
            if (IsEmptyLinkStack(op_stack) ||
                get_priority(*tmp) > get_priority(top_op ? top_op->op : ' '))
            {
                data.op = *tmp;
                PushLinkStack(op_stack, &data);
                break;
            }
            else
            {
                // 弹出操作数和运算符计算
                int num2 = GetTopLinkStack(num_stack)->num;
                PopLinkStack(num_stack);
                int num1 = GetTopLinkStack(num_stack)->num;
                PopLinkStack(num_stack);
                char op = GetTopLinkStack(op_stack)->op;
                PopLinkStack(op_stack);
 
                // 计算结果入操作数栈
                int result = calc_result(num1, num2, op);
                data.num = result;
                PushLinkStack(num_stack, &data);
                
                top_op = GetTopLinkStack(op_stack); // 更新栈顶运算符
            }
        }
        tmp++;
    }
 
    // 处理最后一个数字
    data.num = temp_num;
    temp_num = 0;
    PushLinkStack(num_stack, &data);
 
    // 处理剩余运算符
    while (!IsEmptyLinkStack(op_stack))
    {
        int num2 = GetTopLinkStack(num_stack)->num;
        PopLinkStack(num_stack);
        int num1 = GetTopLinkStack(num_stack)->num;
        PopLinkStack(num_stack);
        char op = GetTopLinkStack(op_stack)->op;
        PopLinkStack(op_stack);
 
        int result = calc_result(num1, num2, op);
        data.num = result;
        PushLinkStack(num_stack, &data);
    }
 
    // 输出最终结果
    top_op = GetTopLinkStack(num_stack);
    int final_result = top_op->num;
    printf("中缀表达式：%s\n计算结果：%d\n", express, final_result);
 
    // 销毁栈
    DestroyLinkStack(num_stack);
    DestroyLinkStack(op_stack);
 
    return 0;
}