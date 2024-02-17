#ifndef LLIST_H__
#define LLIST_H__

typedef void LLIST;

#define LLIST_FORWARD 1
#define LLIST_BACKWORD 2

typedef void llist_op(const void *);
typedef int llist_cmp(const void *, const void *);

LLIST *llist_create(int size);

int llist_insert(LLIST *ptr, const void *data, int mode);

void *llist_find(LLIST *ptr, const void *key, llist_cmp *cmp);

int llist_delete(LLIST *ptr, const void *key, llist_cmp *cmp);

int llist_fetch(LLIST *ptr, const void *key, llist_cmp *cmp, void *data);

void llist_travel(LLIST *, llist_op *);

void llist_destory(LLIST *);

#endif /* LLIST_H__*/