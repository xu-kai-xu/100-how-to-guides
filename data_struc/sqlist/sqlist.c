/*
线性表 增删改查功能源文件
*/

#include "sqlist.h"
#include <stdlib.h>
#include <stdio.h>

sqlist *sqlist_create(void)
{
    sqlist *me = NULL;
    me = malloc(sizeof(*me));
    printf("size of me = %lu\n", sizeof(me));
    printf("size of *me = %lu\n", sizeof(*me));
    if (me == NULL) {
        return NULL;
    }
    me->last = -1;
}

void sqlist_create_1(sqlist **ptr)
{
    *ptr = malloc(sizeof(**ptr));
    if (*ptr == NULL) {
        return;
    }
    (*ptr)->last = -1;
    return;
}

int sqlist_insert(sqlist *me, int i, data_type *data)
{
    printf("me->last = %d\n", me->last);
    if(me->last == DATA_SIZE - 1) {
        return -1;
    }
    if (i < 0 || i > me->last + 1) {
        return -2;
    }

    // 插入
    int j = me->last;
    printf("j = %d\n", j);
    // if (j == -1) {
    //     me->data[++j] = *data;
    //     (me->last)++;
    //     return 0;
    // }

    for (; j >= i; j-- ) {
        me->data[j + 1] = me->data[j];
    }
    (me->last)++;
    me->data[i] = *data;
    printf("insert arr[%d], %d\n", i, me->data[i]);
    return 0;
}

int sqlist_delete(sqlist *me, int i)
{
    if (i < 0 || i > me->last) {
        return -1;  //非法索引值
    }

    for (int j = i + 1; j <= me->last; j++) {
        me->data[j - 1] = me->data[j];
    }
    (me->last)--;
    return 0;
}

int sqlist_is_empty(sqlist *me)
{
    return me->last == -1;
}
int sqlist_set_empty(sqlist *me)
{
    return me->last = -1;
    return 0;
}

int sqlist_get_size(sqlist *me)
{
    return me->last++;
}

int sqlist_find(sqlist *me, data_type *data)
{
    if(sqlist_is_empty(me) == 1) {
        return -1;
    }
    for (int i = 0; i <= me->last; i++) {
        if (me->data[i] == *data) {
            return i;
        }
    }
    return -1;
}

// 假设线性表不重复
int sqlist_union(sqlist *list_1, sqlist *list_2)
{
    // 无重复合并
    // list 1 -> 12 23 34 45 56
    // list 2 -> 78 89 56 23 10
    int i = 0;
    while (i <= list_2->last) {
        if (sqlist_find(list_1, &(list_2->data[i])) == -1) {
            sqlist_insert(list_1, list_1->last + 1, &(list_2->data[i]));
        }

        i++;
    }
}

void sqlist_display(sqlist *me)
{
    if (me->last == -1) {
        return;
    }
    for (int i = 0; i <= me->last; i++) {
        printf("%d ", me->data[i]);
    }
    printf("\n");
    return;
}

int sqlist_destory(sqlist *me)
{
    free(me);
    me = NULL;
    return 0;
}