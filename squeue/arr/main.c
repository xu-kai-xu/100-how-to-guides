#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
    queue *sq =  qu_create();
    if (sq == NULL) {
        exit(1);
    }

    datatype arr[] = {2, 34, 89, 12};

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        qu_enqueue(sq, &arr[i]);
    }

    qu_travel(sq);

    // 队列满后再入队报错;
    datatype tmp = 666;
    int ret = qu_enqueue(sq, &tmp);
    if (ret == -1) {
        printf("入队失败，队列已满\n");
    }

    qu_travel(sq);


    // 出队一次
    qu_dequeue(sq, &tmp);
    printf("出队元素为: %d\n", tmp);
    qu_travel(sq);

    // 清空队列
    qu_clear(sq);
    qu_travel(sq);


    qu_destory(sq);
    exit(0);
}