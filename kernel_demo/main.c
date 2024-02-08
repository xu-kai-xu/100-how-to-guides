#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct score_st {
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
    struct list_head node;
};

void print_s(struct score_st *d)
{
    printf("%d %s %d %d\n", d->id, d->name, d->math, d->chinese);
}

int main()
{
    struct score_st *datap = NULL;
    LIST_HEAD(head);

    for (int i = 0; i < 7; i++) {
        datap = malloc(sizeof(struct score_st));
        if (datap == NULL) {
            exit(1);
        }
        datap->id = i;
        snprintf(datap->name, NAMESIZE, "std %d", i);
        datap->math = rand() % 100;
        datap->chinese = rand() % 100;

        // list_add(&(datap->node), &head);     // 首部插入
        list_add_tail(&(datap->node), &head);   // 尾部插入
    }

    struct list_head *cur = &head;
    __list_for_each(cur, &head) {
        datap = list_entry(cur, struct score_st, node);
        print_s(datap);
    }

    // 查询
    __list_for_each(cur, &head) {
        datap = list_entry(cur, struct score_st, node);
        if (datap->id == 15) {
            break;
        }
    }

    if (cur == &head) {
        printf("not found.\n");
    } else {
        print_s(datap);
    }

    exit(0);
}