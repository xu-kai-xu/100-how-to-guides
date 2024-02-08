#include "list.h"
#include <stdio.h>
#include <stdlib.h>

list *list_create()
{
    list *me = malloc(sizeof(*me));
    if (me == NULL) {
        return NULL;
    }

    me->next = NULL;
    return me;
}

list *list_node_find(list *me, datatype *data)
{
    list *p = me;
    while (p) {
        if (p->data = *data) {
            return p;
        }
    }
    return NULL;
}

int list_insert_at(list *me, int i, datatype *data)
{
    if (i < 0) {
        return -1;
    }
    list *cur = me;
    for (int j = 0; j < i && cur != NULL; j++) {   // 移动到待插入节点的前驱节点
        printf("in inner for loop\n");
        cur = cur->next;
        printf("cur = %p\n", cur);
    }

    if (cur == NULL) {
        printf("cur == NULL, in list_insert_at");
        return -3;
    }

    list *newnode = malloc(sizeof(list));
    if (newnode == NULL) {
        return -2;
    }

    newnode->data = *data;
    printf("newnode->data = %d\n", newnode->data);
    newnode->next = cur->next;
    cur->next = newnode;

    // free(cur);   不能释放，释放会报错
    // cur = NULL;

    return 0;
}

int list_order_insert(list *me, datatype *data)
{
    // 假设列表中的数是从小到大排列的
    list *p = me;
    while (p->next && (p->next->data < *data)) {
        p = p->next;
    }
    list *q = malloc(sizeof(*p));
    if (q == NULL) {
        printf("malloc err.\n");
        return -1;
    }
    q->data = *data;
    q->next = p->next;
    p->next = q;
    return 0;
}

int list_insert_at_start(list *me, datatype *data)
{
    if (me->next == NULL) {
        printf("empty list.\n");
        return -1;
    }

    list *p = malloc(sizeof(list));
    if (p == NULL) {
        printf("malloc err\n");
        return -1;
    }
    p->data = *data;
    p->next = me->next;
    me->next = p;
    return 0;
}

int list_insert_at_end(list *me, datatype *data)
{
    list *p = me;
    while (p->next) {
        p = p->next;
    }

    list *q = malloc(sizeof(list));
    if (q == NULL) {
        printf("malloc err\n");
        return -1;
    }

    q->data = *data;
    p->next = q;
    return 0;
}

int list_delete_at(list *me, int i, datatype *data)
{
    *data = NULL;
    if (i < 0) {
        return -1;
    }
    int j = 0;
    list *p = me;
    list *q = NULL;
    while (j < i && p) {
        j++;
        p = p->next;
    }
    if (p) {
        q = p->next;
        p->next = q->next;
        *data = q->data;
        free(q);
        q = NULL;
        return 0;
    }

    return -2;
}

int list_delete(list *me, datatype *data)
{
    list *p = me;
    while (p->next && (p->next->data != *data)) {
        p = p->next;
    }
    if (p->next == NULL) {
        return -1;
    }
    list *q = p->next;
    p->next = q->next;
    free(q);
    q = NULL;
    return 0;
}

int list_delete_at_start(list *me)
{
    if (!list_isempty(me)) {
        printf("empty list\n");
        return -1;
    }
    list *p = me->next;
    me->next = p->next;
    free(p);
    p = NULL;
    return 0;
}

int list_delete_at_end(list *me)
{
    if (list_isempty(me) == 0) {
        printf("empty list\n");
        return -1;
    }
    list *p = me;
    while(p->next->next) {
        p = p->next;
    }
    list *q = p->next;
    p->next = NULL;
    free(q);
    q = NULL;
}

int list_isempty(list *me)
{
    if (me->next == NULL) {
        return 0;
    }
    return 1;
}

void list_display(list *me)
{
    list *node = me->next;
    if (list_isempty(me) == 0) {
        return;
    }
    for (int i = 0; node != NULL; i++) {
        printf("node %d val = %d\n", i, node->data);
        node = node->next;
    }
    printf("\n");
    free(node);
    node = NULL;
}

void list_destory(list *me)
{
    list *cur = me->next;
    list *next = NULL;
    for (; cur != NULL; cur = next) {
        next = cur->next;
        free(cur);
        cur = NULL;
    }

    free(me);
    me = NULL;
}