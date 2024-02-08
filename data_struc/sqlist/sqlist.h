/*
顺序存储线性表的增 删 改 查 清空
*/

#ifndef SQLIST_H_
#define SQLIST_H_

#define DATA_SIZE 1024
typedef int data_type;

typedef struct {
    data_type data[DATA_SIZE];
    int last;
} sqlist;

sqlist *sqlist_create(void);

void sqlist_create_1(sqlist **);

int sqlist_destory(sqlist *);

int sqlist_insert(sqlist *, int, data_type *);

int sqlist_delete(sqlist *, int);

int sqlist_find(sqlist *, data_type *);

int sqlist_is_empty(sqlist *);

int sqlist_set_empty(sqlist *);

int sqlist_get_size(sqlist *);

void sqlist_display(sqlist *);

// 假设线性表不重复
int sqlist_union(sqlist *, sqlist *);

#endif /* SQLIST_H_ */