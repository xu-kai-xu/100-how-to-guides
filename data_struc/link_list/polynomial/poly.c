/*
带头节点的练习题
*/

#include <stdio.h>
#include <stdlib.h>

// 多项式的数据结构
struct node_st {
    int coef;
    int expo;
    struct node_st *next;
};

struct node_st *poly_create(int a[][2], int n)
{
    struct node_st *me = malloc(sizeof(struct node_st));
    struct node_st *newnode = NULL;
    if (me == NULL) {
        printf("node create failed");
        return NULL;
    }
    me->next = NULL;
    struct node_st *cur = me;

    for (int i = 0; i < n; i++) {
        newnode = malloc(sizeof(*newnode));
        if (newnode == NULL) {
            printf("create node %d failed\n", i);   //错误后需要依次释放全部节点，需要改进
            return NULL;
        }
        newnode->coef = a[i][0];
        newnode->expo = a[i][1];
        newnode->next = NULL;
        cur->next = newnode;
        cur = newnode;
    }
    return me;
}

void poly_show(struct node_st *me)
{
    struct node_st *cur = me->next; //直接指向头节点的下一个节点
    while (cur != NULL) {
        printf("(%d * x ^ %d)", cur->coef, cur->expo);
        cur = cur->next;
    }
    printf("\n");
}

void poly_union(struct node_st *p1, struct node_st *p2)
{
    struct node_st *p = p1->next;
    struct node_st *q = p2->next;
    struct node_st *r = p1; // r指向当前已经连接好的位置

    while (p && q) {
        if (p->expo < q->expo) {
            r->next = p;
            r = p;
            p = p->next;
        } else if (p->expo > q->expo) {
            r->next = q;
            r = q;
            q = q->next;

        } else {    // p->expo == q->expo
            p->coef += q->coef;
            if (p->coef) {
                r->next = p;
                r = p;
            }
            p = p->next;
            q = q->next;
        }
    }

    if (p == NULL) {
        r->next = q;
    } else {
        r->next = p;
    }

}

void poly_destory(struct node_st *me)
{
    struct node_st *cur = me;
    if (cur == NULL) {
        printf("empty node list.\n");
        return;
    }
    struct node_st *next = NULL;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

/*
5 + 2 * x + 8 * x^8 + 3 * x ^ 16
    6 * x + 16 * x ^ 6 - 8 * x ^ 8
*/

int main()
{
    int a[][2] = {{5, 0}, {2, 1}, {8, 8}, {3, 16}};
    int b[][2] = {{6, 1}, {16, 6}, {-8, 8}};
    struct node_st *p1 = poly_create(a, 4);
    if (p1 == NULL) {
        exit(1);
    }
    struct node_st  *p2 = poly_create(b, 3);
    if (p2 == NULL) {
        exit(1);
    }
    poly_show(p1);
    poly_show(p2);

    poly_union(p1, p2);

    poly_show(p1);
    poly_show(p2);

    // poly_destory(p1);
    poly_destory(p2);

    printf("%p %p\n", p1, p2);
    printf("%d %d\n", p1->coef, p2->coef);
    printf("%d %d\n", p1->expo, p2->expo);
    printf("%p %p\n", p1->next->next, p2->next->next);

    exit(0);
}