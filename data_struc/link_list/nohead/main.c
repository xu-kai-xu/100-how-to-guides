#include <stdio.h>
#include <stdlib.h>
#include "nohead_link.h"

int main()
{
    int ret = 0;
    struct node_st *list = NULL;
    struct score_st tmp;
    for (int i = 0; i < 7; i++) {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "stu%d", i);
        tmp.math = rand() % 100;
        tmp.chinese = rand() % 100;

        ret = list_insert_at_start(&list, &tmp);
        if (ret != 0) {
            printf("insert node failed\n");
            exit(1);
        }
    }

    list_show(list);

    printf("\nnow delete \n");
    list_delete_at_start(&list);

    list_show(list);

    printf("\nnow find \n");
    int id = 3;
    struct node_st *find_res = NULL;
    ret = list_find_id(list, &find_res, id);

    printf("%d %s %d %d\n", find_res->data.id, find_res->data.name, find_res->data.math, find_res->data.chinese);



    list_destory(list);

    // test free res
    printf("%p\n", list);
    printf("%p\n", list->next);
    printf("%d\n", list->next->data.chinese);

    exit(0);
}