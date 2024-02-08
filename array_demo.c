/*
 五 数组
 数组 指针 函数

 基本类型: int char float double

 构造类型：结构体 共用体 枚举

 数组是构造类型，在内存当中连续存放

 1. 一维数组
    - 定义
        [存储类型] 数据类型 标识符[下标]; 下标可以是整型常量或整型常量表达式

    - 初始化
        不初始化
        全部初始化
        部分初始化
        static 类型

    - 元素引用
        数组名 + 下标 的方式

    - 数组名
        数组名也是当前数组的起始位置
        数组名是表示地址的常量

    - 数组越界
        数组越界不检查，现在检查了，会报错 `*** stack smashing detected ***: terminated Aborted`

 2. 二维数组

 3. 字符数组

*/

/* 一维数组练习题目
1. fibonacci数列
2. 数据排序：冒泡排序 选择排序 快速排序
3. 进制转换
4. 删除法求质数

*/

#include <stdio.h>
#include <stdlib.h>

#define M 3

void define_array()
{
    int arr[M];  // 定义数组 auto 类型，没有自动初始化

    printf("sizeof(arr) = %lu\n", sizeof(arr));
    for (int i = 0; i < M; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);  // 不初始化会随机赋值
        printf("address of arr[%d] = %p\n", i, &arr[i]);
    }
}

void define_init()
{
    // 全部初始化
    int arr[M] = {1, 2, 3};  // 定义数组 auto 类型，没有自动初始化

    printf("sizeof(arr) = %lu\n", sizeof(arr));
    for (int i = 0; i < M; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);  // 不初始化会随机赋值
        printf("address of arr[%d] = %p\n", i, &arr[i]);
    }
}

void define_part_init()
{
    // 部分初始化，其他元素初始化为0
    int arr[M] = {1};  // 定义数组 auto 类型，没有自动初始化

    printf("sizeof(arr) = %lu\n", sizeof(arr));
    for (int i = 0; i < M; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);  // 不初始化会随机赋值
        printf("address of arr[%d] = %p\n", i, &arr[i]);
    }
}

void define_static()
{
    // 指定存储类型为 static
    static int arr[M];  // 定义数组 auto 类型，没有自动初始化

    printf("sizeof(arr) = %lu\n", sizeof(arr));
    for (int i = 0; i < M; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);  // 不初始化会随机赋值
        printf("address of arr[%d] = %p\n", i, &arr[i]);
    }
}

// 数组越界
void array_overbound()
{
    int arr[M] = {1, 2, 3};
    arr[3] = 10; // 越界
    printf("arr[3] = %d\n", arr[3]);
    for (int i = 0; i < M; i++)
    {
        printf("arr[%d] = %d\n", i, arr[i]);  // 不初始化会随机赋值
        printf("address of arr[%d] = %p\n", i, &arr[i]);
    }
}

//array 原位逆序
static void array_reverse(int *arr, int i, int j)
{
    int tmp = 0;
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

//fibonacci数列的前10项
#define FIBNUM 10

static void fib()
{
    int arr[10] = {1, 1};

    for (int i = 2; i < FIBNUM; i++) {
        arr[i] = arr[i - 1] + arr[i - 2];
    }

    for (int j = 0; j < FIBNUM; j++) {
        printf("fib[i] = %d\n", arr[j]);
    }

    printf("fibonacci reverse: \n");

    int m = 0;
    int n = FIBNUM - 1;

    while (m < n) {
        array_reverse(arr, m++, n--);
    }

    for (int k = 0; k < FIBNUM; k++) {
        printf("fib[i] = %d\n", arr[k]);
    }
}


#define ARR_SIZE 10

// 冒泡排序
/*
 依次比较相邻元素，排号，然后重复多轮，直到没有发生交换顺序为止
*/

static void bubble_sort(int *arr, int size)
{
    // 不能在函数里求数组大小，因为数组会退化为指针
    int tmp = 0;
    printf("size = %d\n", size);
    for (int i = 0; i < size - 1; i ++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

static void bubble_sort_2(int *arr, int size)
{
    // 改进版 bubble sort
    // 当某一次完全没有交换时，就说明已经排好了
    int swap_flag; // 发生交换的标志
    int i, tmp;
    while (1) {
        swap_flag = 0;  // 每一轮都重新设置标志位
        for (i = 0; i < size - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                swap_flag = 1;
            }
        }

        if (!swap_flag) {
            break;
        }
    }
}

// 寻找最小值的下标
int find_min(int *arr, int n)
{
    int idx_min = 0;
    int mini = arr[0];
    for (int i = 0; i < n; i++) {
        if (mini > arr[i]) {
            mini  = arr[i];
            idx_min = i;
        }
    }
    return idx_min;
}

/*
 选择排序法
*/
static void selection_sort(int *arr, int n)
{
    int idx_min = 0;
    int tmp = 0;

    for (int i = 0; i < n; i++) {
        idx_min = find_min(arr + i, n - i) + i;
        tmp = arr[i];
        arr[i] = arr[idx_min];
        arr[idx_min] = tmp;
    }
}


int main()
{
    // define_array();
    // define_init();
    // define_part_init();
    // define_static();
    // array_overbound();
    // fib();
    int arr[ARR_SIZE] = {12, 8, 45, 30, 98, 67, 2, 7, 11, 68};
    for (int i = 0; i < ARR_SIZE; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    // bubble_sort(arr, ARR_SIZE);
    // bubble_sort_2(arr, ARR_SIZE);
    selection_sort(arr, ARR_SIZE);
    // find_min(arr, ARR_SIZE);
    for (int j = 0; j < ARR_SIZE; j++) {
        printf("arr[%d] = %d\n", j, arr[j]);
    }

    // int t = find_min(arr, ARR_SIZE);
    // printf("t = %d\n", t);
    exit(0);
}
