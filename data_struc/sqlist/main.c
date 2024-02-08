#include <stdio.h>
#include <stdlib.h>
#include "sqlist.h"

int main()
{
    sqlist *list = NULL;
    data_type arr[] = { 12, 23, 34, 45, 56};
    data_type arr_1[] = { 89, 90, 78, 67, 56, 43};
    list = sqlist_create();
    // sqlist_create_1(&list); // 第二种创建方式
    if (list == NULL) {
        fprintf(stderr, "sqlist_create list failed.\n");
        exit(1);
    }

    sqlist *list_1 = sqlist_create();
    if (list_1 == NULL) {
        fprintf(stderr, "sqlist_create list_1 failed.\n");
        exit(1);
    }

    int err = 0;
    // printf("sizeof arr = %lu\n", sizeof(arr) / sizeof(arr[0]));
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        err = sqlist_insert(list, i, arr + i);
        printf("err = %d\n", err);
        if (err == 0) {
            continue;   // success
        } else if ( err == -1) {
            fprintf(stderr, "sqlist is full.\n");
            exit(1);
        } else if (err == -2) {
            fprintf(stderr, "insert position error.\n");
            exit(1);
        } else {
            fprintf(stderr, "unknown error type.\n");
            exit(1);
        }
    }

    sqlist_display(list);

    for (int i = 0; i < sizeof(arr_1) / sizeof(arr_1[0]); i++) {
        err = sqlist_insert(list_1, i, arr_1 + i);
        printf("err = %d\n", err);
        if (err == 0) {
            continue;   // success
        } else if ( err == -1) {
            fprintf(stderr, "sqlist is full.\n");
            exit(1);
        } else if (err == -2) {
            fprintf(stderr, "insert position error.\n");
            exit(1);
        } else {
            fprintf(stderr, "unknown error type.\n");
            exit(1);
        }
    }
    sqlist_display(list_1);



    // // 删除
    // printf("\ndelete\n");
    // sqlist_delete(list, 1);
    // sqlist_display(list);

    // join
    printf("\njoin\n");
    sqlist_union(list, list_1);
    sqlist_display(list);
    sqlist_display(list_1);


    sqlist_destory(list);
    sqlist_destory(list_1);
    exit(0);
}