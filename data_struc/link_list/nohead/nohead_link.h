#include <stdio.h>
#include <stdlib.h>

#define NAMESIZE 32

struct score_st {
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};

struct node_st {
    struct score_st data;
    struct node_st *next;   // 自引用指针
};

int list_insert_at_start(struct node_st **me, struct score_st *data);
void list_show(struct node_st *me);
int list_find_id(struct node_st *me, struct node_st **res_node, int id);
int list_delete_at_start(struct node_st **list);
void list_destory(struct node_st *me);