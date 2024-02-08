#ifndef SQSTACK_H__
#define SQSTACK_H__

#define MAXSIZE 5

typedef int datatype;

typedef struct node_st {
    datatype data[MAXSIZE];
    int top;
} sqstack;

sqstack *st_create(void);

int st_isempty(sqstack * st);

int st_push(sqstack *st, datatype *data);

int st_pop(sqstack *st, datatype *data);

int st_top(sqstack *st, datatype *data);  // 查看栈顶元素，不弹出

void st_travel(sqstack *st);

void st_destory(sqstack *st);

#endif /* SQSTACK_H__ */