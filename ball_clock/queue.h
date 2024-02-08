#ifndef QUEUE_H__
#define QUEUE_H__

#include <stdio.h>

#define MAXSIZE 32

typedef int datatype;

typedef struct node_queue_st {
    datatype data[MAXSIZE];
    int head, tail;
} queue;

queue *qu_create(void);
int qu_isempty(queue *sq);
int qu_isfull(queue *sq);
int qu_enqueue(queue *sq, datatype *x);
int qu_dequeue(queue *sq, datatype *x);
int qu_clear(queue *sq);
void qu_travel(queue *sq);
void qu_destory(queue *sq);

#endif /* QUEUE_H__ */