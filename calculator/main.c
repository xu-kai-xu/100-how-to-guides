#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "sqstack.h"

#define EXP_SIZE 1000

static void compute(sqstack *snum, datatype *op)
{
    datatype n1, n2, n;
    st_pop(snum, &n2);
    st_pop(snum, &n1);

    switch(*op) {
        case '+':
            n = n1 + n2;
            break;
        case '-':
            n = n1 - n2;
            break;
        case '*':
            n = n1 * n2;
            break;
        case '/':
            n = n1 / n2;
            break;
        default:
            exit(1);
    }
    printf("compute detail: %d %c %d = %d\n", n1, *op, n2, n);
    fflush(stdout);
    st_push(snum, &n);
}

static int get_pri(datatype op)
{
    switch(op) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}

// void deal_bracket(sqstack *snum, sqstack *sop)
// {
//     datatype old_op;

//     st_top(sop, &old_op);
//     while (old_op != '(') {
//         st_pop(sop, &old_op);
//         // st_travel(sop);
//         compute(snum, &old_op);
//         st_top(sop, &old_op);
//     }
//     st_pop(sop, &old_op);
// }

void deal_bracket(sqstack *snum, sqstack *sop)
{
    datatype old_op;

    st_pop(sop, &old_op);
    while (old_op != '(') {
        compute(snum, &old_op);
        st_pop(sop, &old_op);
    }
}


static void deal_op(sqstack *snum, sqstack *sop, int op)
{
    if(st_isempty(sop) || op == '(') {
        st_push(sop, &op);
        return;
    }

    datatype old_op;
    st_top(sop, &old_op);
    if (get_pri(op) > get_pri(old_op)) {
        st_push(sop, &op);
        return;
    }

    while (get_pri(op) <= get_pri(old_op)) {
        st_pop(sop, &old_op);
        compute(snum, &old_op);
        if(st_isempty(sop)) {
            break;
        }
        st_top(sop, &old_op);
    }
    st_push(sop, &op);
}

int main()
{
    char str[EXP_SIZE] = {0};
    // char str[EXP_SIZE] = "(11 + 3) * 2 - 5 * 9";
    // 接收用户输入的表达式
    printf("请输入表达式：");
    fgets(str, EXP_SIZE, stdin);
    printf("需要计算的表达式是：%s\n", str);


    int i = 0;
    int value = 0;
    int flag = 0;  // 0: operator, 1: number

    sqstack *snum = st_create();
    if (snum == NULL) {
        exit(1);
    }

    sqstack *sop = st_create();
    if (sop == NULL) {
        exit(1);
    }

    while (str[i] != '\0') {
        if (str[i] == ' ') {
            i++;
            continue;
        }
        if (isdigit(str[i])) {
            value = value * 10 + str[i] - '0';
            flag = 1;
        } else {
            if (flag) {
                st_push(snum, &value);
                value = 0;
                flag = 0;
            }
            if (str[i] == ')') {
                deal_bracket(snum, sop);
            } else { // + - * / (
                deal_op(snum, sop, str[i]);
            }
        }
        i++;
    }

    if (flag) {
        st_push(snum, &value);
    }

    datatype old_op;
    while(!st_isempty(sop)) {
        st_pop(sop, &old_op);
        compute(snum, &old_op);
    }

    // 打印最后的计算结果
    st_pop(snum, &value);
    printf("%s = %d\n", str, value);
    fflush(stdout);

    st_destory(snum);
    st_destory(sop);

    exit(0);
}