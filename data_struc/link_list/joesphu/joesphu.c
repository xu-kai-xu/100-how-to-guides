/*
约瑟夫环算法

单向环链

不使用头节点更方便
*/

#include <stdio.h>
#include <stdlib.h>

#define JOSE_NUM 8

struct node_st {
    int data;
    struct node_st *next;
};

/*
单向环链的创建方式
1. 按单向链表的方式来创建
2. 让每一个链表的指针指向自己，即时时刻刻都是环链
*/
struct node_st *jose_create(int n)
{
    int i = 1;

    // 创建首节点
    struct node_st *me = malloc(sizeof(struct node_st));
    if (me == NULL) {
        return NULL;
    }
    me->data = i++;
    me->next = me;
    // printf("me->data = %d\n", me->data);

    struct node_st *newnode = NULL;
    struct node_st *cur = me;
    for (; i <= JOSE_NUM; i++) {
        newnode = malloc(sizeof(struct node_st));
        if (newnode == NULL) {
            return NULL;
        }
        newnode->data = i;
        newnode->next = me; // 新节点的后继节点都指向起始节点
        cur->next = newnode;
        cur = newnode;
    }
    return me;
}

void jose_show(struct node_st *me)
{
    struct node_st *list = me;
    // printf("me->data = %d\n", me->data);
    // for (int i = 0; i < JOSE_NUM; i++) {
    //     printf("%d ", list->data);
    //     list = list->next;
    // }
    // printf("\n");

    for (; list->next != me; list = list->next) {
        printf("%d ", list->data);
    }
    printf("%d\n", list->data); // 循环会少打印一个节点，即尾节点
}

struct node_st *jose_kill_diy(struct node_st *me, int n)
{
    struct node_st *cur = me;
    struct node_st *remove_node = NULL;
    int i = 1;
    while (cur->next != cur) {
        if (i == n - 1) {
            remove_node = cur->next;
            cur->next = cur->next->next;
            cur = cur->next;
            printf("remove node, data = %d\n", remove_node->data);
            free(remove_node);
            remove_node = NULL;
            i--;
        } else {
            cur = cur->next;
            i++;
        }
    }
    return cur;
}

struct node_st *jose_kill(struct node_st *me, int n)
{
    struct node_st *cur = me;
    struct node_st *node = NULL;
    int i = 1;

    while (cur != cur->next) {
        while(i < n) {
            node = cur;
            cur = cur->next;
            i++;
        }
        printf("remove node %d\n", cur->data);
        node->next = cur->next;
        free(cur);

        cur = node->next;
        i = 1;
    }
    printf("\n");
    return cur;
}

int main()
{
    struct node_st *list = jose_create(JOSE_NUM);  //创建无头单向循环链表
    if (list == NULL) {
        printf("malloc err in main\n");
        return 1;
    }

    jose_show(list);

    int n = 3;

    struct node_st *res = jose_kill(list, n);
    // struct node_st *res = jose_kill_diy(list, n);

    jose_show(res);

    exit(0);
    // jose_destory();
}