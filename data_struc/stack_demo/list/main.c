#include <stdio.h>
#include <stdlib.h>

#include <stack.h>

#define NAMESIZE 32

struct score_st {
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};

void print_s(void *record)
{
    struct score_st *r = record;
    printf("%d %s %d %d\n", r->id, r->name, r->math, r->chinese);
}

int main()
{
    STACK *st = stack_create(sizeof(struct score_st));
    if (st == NULL) {
        printf("stack_create failed\n");
        exit(1);
    }

    struct score_st tmp;
    for (int i = 0; i < 7; i++) {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "stu %d", i);
        tmp.math = rand() % 100;
        tmp.chinese = rand() % 100;
        if (stack_push(st, &tmp) != 0) {
            printf("stack_push failed");
            exit(1);
        }
    }

    int ret = 0;
    while(ret == 0) {
        ret = stack_pop(st, &tmp);
        if (ret != 0) {
            printf("stack_pop failed\n");
            break;
        }
        print_s(&tmp);
    }

    stack_destory(st);
    exit(0);
}