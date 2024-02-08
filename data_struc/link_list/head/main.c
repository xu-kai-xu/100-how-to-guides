#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    list *node = list_create();
    if (node == NULL) {
        exit(1);
    }

    datatype arr[] = {12, 9, 23, 2, 34, 6, 45};
    for (int i = 0; i < sizeof(arr) / sizeof(*arr); i++) {
        if (list_order_insert(node, &arr[i])) {
            exit(1);
        }
    }

    list_display(node);

    datatype data = 34;

    int ret = list_delete_at_end(node);
    printf("ret = %d, \n", ret);
    list_display(node);

    list_destory(node);
    exit(0);
}