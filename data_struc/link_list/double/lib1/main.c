#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"

#define NAMESIZE 32

struct score_st {
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};

static void print_s(const void *record)
{
    const struct score_st *r = record;
    printf("%d %s %d %d\n", r->id, r->name, r->math, r->chinese);
}

static int id_cmp(const void *key, const void *record)
{
    const int *k = key;
    const struct score_st *r = record;

    return (*k - r->id);
}

static int name_cmp(const void *key, const void *record)
{
    const char *k = (char *)key;
    const struct score_st *r = record;
    return strcmp(k, r->name);
}

int main()
{
    LLIST *handler = llist_create(sizeof(struct score_st));
    if (handler == NULL) {
        exit(1);
    }

    struct score_st tmp = {0};
    int ret = 0;
    for (int i = 0; i < 7; i++) {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "stu %d", i);
        tmp.math = rand() % 100;
        tmp.chinese = rand() % 100;

        ret = llist_insert(handler, &tmp, LLIST_BACKWORD);
        if (ret != 0) {
            exit(1);
        }
    }
    llist_travel(handler, print_s);

    printf("\n=========test find\n\n");

    int id = 4;
    struct score *data = llist_find(handler, &id, id_cmp);

    if (data == NULL) {
        printf("no record for id = [%d]\n", id);
    } else {
        print_s(data);
    }

    printf("\n=========test delete according to id\n\n");
    ret = llist_delete(handler, &id, id_cmp);
    if (ret != 0) {
        printf("delete node with id [%d] failed\n", id);
    }

    llist_travel(handler, print_s);

    // 根据 name删除
    printf("\n=========test delete according to name\n\n");
    // char del_name[] = "stu 5";
    char *del_name = "stu 5";    // del_name 本身就是地址了
    printf("%s\n", del_name);
    ret = llist_delete(handler, del_name, name_cmp);
    if (ret != 0) {
        printf("delete node with name [%s] failed\n", del_name);
    }

    llist_travel(handler, print_s);

    llist_destory(handler);
    exit(0);
}