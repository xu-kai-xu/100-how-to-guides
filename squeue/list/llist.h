#ifndef LLIST_H__
#define LLIST_H__

#define LLIST_FORWARD 1
#define LLIST_BACKWORD 2

typedef void llist_op(const void *);
typedef int llist_cmp(const void *, const void *);

struct llist_node_st {
    struct llist_node_st *prev;
    struct llist_node_st *next;
    char data[0];   // 零长数组
};

typedef struct llist_head {
    int size;
    struct llist_node_st head;
    int (*insert)(struct llist_head *ptr, const void *data, int mode);
    void *(*find)(struct llist_head *ptr, const void *key, llist_cmp *cmp);
    int (*delete)(struct llist_head *ptr, const void *key, llist_cmp *cmp);
    int (*fetch)(struct llist_head *ptr, const void *key, llist_cmp *cmp, void *data);
    void (*travel)(struct llist_head *ptr, llist_op *op);
} LLIST;

LLIST *llist_create(int size);
void llist_destory(LLIST *);

#endif /* LLIST_H__*/