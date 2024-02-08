#include <stdio.h>
#include <stdlib.h>

#include "sqstack.h"

int main()
{
    datatype arr[] = {19, 23, 0, 67};
    sqstack *st = st_create();
    if (st == NULL) {
        exit(1);
    }

    for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
        st_push(st, &arr[i]);
    }

    st_travel(st);

    datatype tmp = 0;
    int ret = st_push(st, &tmp);
    if (ret != 0) {
        printf("push failed.\n");
    }
    st_travel(st);

    ret = st_pop(st, &tmp);
    if (ret != 0) {
        printf("pop failed.\n");
    } else {
        printf("poped [%d] from stack.\n", tmp);
    }
    st_travel(st);

    while (st_pop(st, &tmp) == 0) {
        printf("poped [%d] from stack.\n", tmp);
    }

    st_destory(st);
    exit(0);
}