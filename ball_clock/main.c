#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"
#include "queue.h"

#define NR_BALL 27

static int check(queue *qu) {
    int i = (qu->head + 1) % MAXSIZE;

    while (i != qu->tail) {
        if (qu->data[i % MAXSIZE] > qu->data[(i + 1) % MAXSIZE]) {
            return 0;
        }

        i = (i + 1) % MAXSIZE;
    }
    qu_travel(qu);
    return 1;
}

int main()
{
    // 创建队列和栈
    queue *qu = qu_create();
    if (qu == NULL) {
        exit(1);
    }

    sqstack *st_min = st_create();
    if (st_min == NULL) {
        exit(1);
    }

    sqstack *st_fivemin = st_create();
    if (st_fivemin == NULL) {
        exit(1);
    }

    sqstack *st_hour = st_create();
    if (st_hour == NULL) {
        exit(1);
    }

    // 创建球
    for (int i = 1; i <= NR_BALL; i++)
    {
        qu_enqueue(qu, &i);
    }

    qu_travel(qu);


    // 模拟
    printf("开始模拟......\n");
    int cur_ball, tmp_ball;
    int tick_count = 0;
    while (1) {
        if (qu_isempty(qu)) {
            printf("tick_count = %d\n", tick_count);
            printf("error: ball queue is empty.\n");
            break;
        }
        qu_dequeue(qu, &cur_ball);
        tick_count++;

        if (st_min->top < 4) {
            st_push(st_min, &cur_ball);
            continue;
        } else {
            while (!st_isempty(st_min)) {
                st_pop(st_min, &tmp_ball);
                qu_enqueue(qu, &tmp_ball);
            }
            qu_dequeue(qu, &tmp_ball);
            st_push(st_fivemin, &tmp_ball);
        }

        if (st_fivemin->top < 11) {
            continue;
        } else {
            while (!st_isempty(st_fivemin)) {
                st_pop(st_fivemin, &tmp_ball);
                qu_enqueue(qu, &tmp_ball);
            }
            qu_dequeue(qu, &tmp_ball);
            st_push(st_hour, &tmp_ball);
        }

        if (st_hour->top < 11) {
            continue;
        } else {
            while (!st_isempty(st_hour)) {
                st_pop(st_hour, &tmp_ball);
                qu_enqueue(qu, &tmp_ball);
            }
        }

        // 到这里，所有的球都已经回到了原来的队列中
        qu_travel(qu);
        printf("tick_count = %d\n", tick_count);
        break;
    }

    // 释放资源
    qu_destory(qu);
    st_destory(st_min);
    st_destory(st_fivemin);
    st_destory(st_hour);

    exit(0);
}