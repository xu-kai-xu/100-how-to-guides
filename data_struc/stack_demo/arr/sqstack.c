#include "sqstack.h"
#include <stdlib.h>
#include <stdio.h>

sqstack *st_create(void)
{
    sqstack *st = malloc(sizeof(sqstack));
    if (st == NULL) {
        return NULL;
    }
    st->top = -1;   // 空栈
    return st;
}

int st_isempty(sqstack * st)
{
    return (st->top == -1);

}

int st_push(sqstack *st, datatype *data)
{
    if (st->top == MAXSIZE - 1) {
        return -1; //   栈满
    }
    st->data[++(st->top)] = *data;
    return 0;
}

int st_pop(sqstack *st, datatype *data)
{
    if (st_isempty(st)) {
        return -1; // 空栈
    }
    *data = st->data[(st->top)--];
    return 0;
}

int st_top(sqstack *st, datatype *data)  // 查看栈顶元素，不弹出
{
    if (st_isempty(st)) {
        return -1; // 空栈
    }
    *data = st->data[st->top];
    return 0;
}

void st_travel(sqstack *st)
{
    if (st_isempty(st)) {
        return;
    }
    for (int i = 0; i <= st->top; i++) {
        printf("%d\n", st->data[i]);
    }
    printf("\n");
}


void st_destory(sqstack *st)
{
    free(st);
}

