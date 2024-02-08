/*
顺序存储循环队列，
头指针指向的位置不存储数据，为了区分队列为空和队列为满的情况

*/

#include "queue.h"

#include <stdlib.h>
#include <stdio.h>

queue *qu_create(void)
{
    queue *sq = malloc(sizeof(*sq));
    if (sq == NULL) {
        return NULL;
    }
    sq->head = 0;
    sq->tail = 0;
    return sq;
}

int qu_isempty(queue *sq)
{
    if (sq->head == sq->tail) {
        return 1; // 队列为空
    }
    return 0;  // 队列不为空
}

int qu_isfull(queue *sq)
{
    if (( sq->tail + 1) % MAXSIZE == sq->head) {
        return 1;  // 队列满
    }
    return 0;  // 队列不满
}

int qu_enqueue(queue *sq, datatype *x)
{
    // 队列满
    if (qu_isfull(sq)) {
        return -1;
    }
    // 先移动尾指针，再入队
    sq->tail = (sq->tail +1) % MAXSIZE;
    sq->data[sq->tail] = *x;
    return 0;
}

int qu_dequeue(queue *sq, datatype *x)
{
    if (qu_isempty(sq)) {
        return -1;
    }
    // 先移动头指针，再出队，头指针指向的位置总是没有元素的
    sq->head = (sq->head + 1) % MAXSIZE;
    *x = sq->data[sq->head];
    return 0;
}

int qu_clear(queue *sq)
{
    // 队列为空的条件
    sq->head = sq->tail;
    return 0;
}

void qu_travel(queue *sq)
{
    if (qu_isempty(sq)) {
        return;
    }
    int i = (sq->head + 1) % MAXSIZE;
    while (i != sq->tail) {
        printf("%d ", sq->data[i]);
        i = (i + 1) % MAXSIZE;
    }
    // 当i = tail时循环结束，但tail所指的元素还未打印
    printf("%d ", sq->data[i]);
    printf("\n");
}

void qu_destory(queue *sq)
{
    free(sq);
    sq = NULL;
}