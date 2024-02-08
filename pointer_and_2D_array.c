/*
 指针与二维数组复习
*/

#include <stdio.h>
#include <stdlib.h>

// type name = values;

/*
行列地址

*/

int main()
{
    int a[2][3] = {1, 2, 3, 4, 5, 6};
    int i = 0;
    int j = 0;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            printf("%p -> %d\n", &a[i][j], a[i][j]);
        }
        printf("\n");
    }

    int *p = &a[0][0];

    printf("%p -> %d\n", p, *p);
    printf("%p -> %d\n", p + 1, *(p + 1));

    int *q = *(a + 0);
    printf("%p -> %d\n", q, *q);
    printf("%p -> %d\n", q + 1, *(q + 1));

    printf("\n");
    int arr[3][4] = { {1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12} };
    int (*ptr)[4] = arr;  // 指向二维数组的指针

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            printf("%p -> %d\n", &arr[i][j], arr[i][j]);
        }
        printf("\n");
    }

    int element = (*ptr)[2];  // 访问第一行第三列的元素
    printf("%p -> %d\n", ptr, **ptr);
    printf("%p -> %d\n", ptr + 1, **(ptr + 1));
    printf("%p -> %d\n", *ptr + 1, *(*ptr + 1));

}