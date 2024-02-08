// 无头节点链表
#include <stdio.h>
#include <stdlib.h>
#include "nohead_link.h"

// 首部插入
int list_insert_at_start(struct node_st **me, struct score_st *data)
{
    struct node_st *new = malloc(sizeof(struct node_st));
    if (new == NULL) {
        printf("malloc err\n");
        return -1;
    }
    new->data = *data;
    new->next = *me;
    *me = new;
    return 0;
}

void list_show(struct node_st *me)
{
    struct node_st *cur = NULL;
    for (cur = me; cur != NULL; cur = cur->next) {
        printf("%d %s %d %d\n", cur->data.id, cur->data.name, cur->data.math, cur->data.chinese);
    }
}

int list_delete_at_start(struct node_st **list)
{
    if (*list == NULL) {
        printf("delete node failed.\n");
        return -1;
    }
    struct node_st *next_node = (*list)->next;
    free(*list);
    *list = NULL;
    *list = next_node;
    return 0;
}

int list_find_id(struct node_st *me, struct node_st **res_node, int id)
{
    struct node_st *cur = me;
    while (cur != NULL) {
        if (cur->data.id == id) {
            *res_node = cur;
            return 0;
        }
        cur = cur->next;
    }
    return -1;   // 没找到
}

void list_destory(struct node_st *me)
{
    if (me == NULL) {
        return;
    }

    struct node_st *cur = me;
    struct node_st *next = cur->next;

    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = NULL;
        cur = next;
    }
}