#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"
#include "queue.h"

#define NR_BALL 27

static int check(queue *qu) {
    // 检查队列中的球，是否按从小到大排列
    // 如果是，返回1；否则返回0
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
    // 1. 从队列中取出一个球，放入分钟的栈中
    int t = 0;
    int value = 0;
    int time = 0;
    while (1) {
        qu_dequeue(qu, &t);
        time++;

        // 分钟栈未满
        if (st_min->top < 3) {
            st_push(st_min, &t);
        } else {
            // 分钟栈满，将分钟栈中的球放入队列
            while(!st_isempty(st_min)) {
                st_pop(st_min, &value);
                qu_enqueue(qu, &value);
            }

            // 如果5分钟栈未满，从队列中取一个球放到5分钟栈中
            if (st_fivemin->top < 10) {
                st_push(st_fivemin, &t);
            } else {
                //  5分钟栈满，将5分钟栈中的球出栈，放入队列
                while (!st_isempty(st_fivemin)) {
                    st_pop(st_fivemin, &value);
                    qu_enqueue(qu, &value);
                }

                // 如果小时栈未满，从队列中取一个球放到小时栈中
                if (st_hour->top < 10) {
                    st_push(st_hour, &t);
                } else {
                    // 小时栈满，将小时栈中的球出栈，放入队列
                    while (!st_isempty(st_hour)) {
                        st_pop(st_hour, &value);
                        qu_enqueue(qu, &value);
                    }

                    // 循环开始，出队列的球，需要重新放入队列，否则少一个球
                    qu_enqueue(qu, &t);

                    // 此时队列中的球数量为27，如果队列中的球是有序的，说明模拟结束
                    if (check(qu)){
                        break;
                    }

                    // 如果队列中的球不是有序的，说明模拟还未结束，将队列中的球重新放入小时栈中
                    // qu_enqueue(qu, &t);
                }
            }
        }
    }

    printf("time = %d.\n", time);
    qu_travel(qu);

    qu_destory(qu);
    st_destory(st_min);
    st_destory(st_fivemin);
    st_destory(st_hour);

    exit(0);
}

/*
这个解法其实有个问题：
比如分钟栈最多是5个。按说应该是，满了5个之后依次弹出，即如果原来有4个，也需要把第五个放进去之后
再全部弹出。

但现在的解法是，分钟栈最多只能有4个球，不能有5个球。
*/