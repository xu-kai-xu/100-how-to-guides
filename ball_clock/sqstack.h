#ifndef SQSTACK_H__
#define SQSTACK_H__

#define SIZE 32

typedef int type;

typedef struct node_stack_st {
    type data[SIZE];
    int top;
} sqstack;

sqstack *st_create(void);

int st_isempty(sqstack * st);

int st_push(sqstack *st, type *data);

int st_pop(sqstack *st, type *data);

int st_top(sqstack *st, type *data);  // 查看栈顶元素，不弹出

void st_travel(sqstack *st);

void st_destory(sqstack *st);

#endif /* SQSTACK_H__ */