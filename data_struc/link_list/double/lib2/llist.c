#include "llist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LLIST *llist_create(int size)
{
    LLIST *new = malloc(sizeof(LLIST));
    if (new == NULL) {
        return NULL;
    }

    new->size = size;
    new->head.prev = &(new->head);
    new->head.next = &(new->head);

    return new;
}

int llist_insert(LLIST *ptr, const void *data, int mode)
{
    struct llist_node_st *newnode = malloc(sizeof(struct llist_node_st));
    if (newnode == NULL) {
        return -1;
    }
    newnode->data = malloc(ptr->size);
    if (newnode->data == NULL) {
        free(newnode);
        newnode = NULL;
        return -2;
    }
    memcpy(newnode->data, data, ptr->size);

    if (mode == LLIST_FORWARD) {
        // 首部插入
        newnode->prev = &(ptr->head);
        newnode->next = ptr->head.next;
    } else if (mode == LLIST_BACKWORD) {
        newnode->prev = ptr->head.prev;
        newnode->next = &(ptr->head);
    } else {
        printf("unrecognized mode, %d\n", mode);
        return -3;
    }
    newnode->prev->next = newnode;
    newnode->next->prev = newnode;
    return 0;
}

void llist_travel(LLIST * ptr, llist_op *op)
{
    struct llist_node_st *cur = ptr->head.next;
    while (cur != &(ptr->head)) {
        op(cur->data);  //回调函数
        cur = cur->next;
    }
}

static struct llist_node_st *find_(LLIST *ptr, const void *key, llist_cmp *cmp)
{
    struct llist_node_st *cur = ptr->head.next;
    while (cur != &(ptr->head)) {
        if (cmp(key, cur->data) == 0) {
            break;
        }
        cur = cur->next;
    }
    return cur;
}

void *llist_find(LLIST *ptr, const void *key, llist_cmp *cmp)
{
    return find_(ptr, key, cmp)->data;
}

int llist_delete(LLIST *ptr, const void *key, llist_cmp *cmp)
{
    struct llist_node_st *node = find_(ptr, key, cmp);
    if (node == &(ptr->head))   // 找不到，返回头节点地址
    {
        printf("find no matched node.\n");
        return -1;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node->data);
    node->data = NULL;
    free(node);
    node = NULL;
    return 0;
}

int llist_fetch(LLIST *ptr, const void *key, llist_cmp *cmp, void *data)
{
    struct llist_node_st *node = find_(ptr, key, cmp);
    if (node == &(ptr->head))   // 找不到，返回头节点地址
    {
        printf("find no matched node.\n");
        return -1;
    }
    node->prev->next = node->next;
    node->next->prev = node->prev;

    if (data != NULL) {
        memcpy(data, node->data, ptr->size);
    }
    free(node->data);
    node->data = NULL;
    free(node);
    node = NULL;
    return 0;
}


void llist_destory(LLIST *ptr)
{
    struct llist_node_st *cur = ptr->head.next;  //指向第一个有效节点
    struct llist_node_st *next_node = NULL;  //指向当前节点下一个节点

    while (cur->next != &(ptr->head)) {
        next_node = cur->next;
        free(cur->data);
        cur->data = NULL;
        free(cur);
        cur = next_node;
    }
    cur = NULL;

    free(ptr);
    ptr = NULL;
}
