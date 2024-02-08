/*
七 函数

1. 函数定义
    数据类型 函数名(数据类型 形参名, 数据类型 形参名, ……)

main 函数的参数
int main(int argc, char *argv[])
int argc 计算传入了多少个参数
char *argv[]，是一个字符型的指针数组

argv 最后会有一个空指针，来表示当前存储的结束

函数声明与函数定义

2. 函数传参
    值传递
    地址传递
    全局变量

3. 函数调用
    嵌套调用
    递归调用

4. 函数与数组
    函数与一维数组
    函数与二维数组
    函数与字符数组

5. 函数与指针
    指针函数，是个函数，返回值是指针
        定义：返回值 * 函数名(形参);
        例子：int *fun(int);
    函数指针，是个指针，指向被调用的函数
        定义：类型 (*指针变量)(形参);
        例子：int (*p)(形参列表);

    函数指针数组
        定义：类型 (*数组名[数组下标])(形参)
        例子：int (*arr[n])(int);

    指向指针函数的函数指针数组
        定义：int * (*funcs[N])(int, int, ...)
*/

#include <stdio.h>
#include <stdlib.h>

// 函数参数的值传递
void print_val(int a, int b)
{
    printf("a = %d, b = %d\n", a, b);
}

// 地址传递
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// 嵌套调用，a调用b，b调用c，c调用d ……
// 返回一串数中的最大值和最小值的差值
int max(int a, int b, int c)
{
    int tmp;
    tmp = a > b ? a: b;
    return tmp > c ? tmp : c;
}

int min(int a, int b, int c)
{
    int tmp;
    tmp = a < b ? a : b;
    return tmp < c ? tmp : c;
}

int dist(int a, int b, int c)
{
    return max(a, b, c) - min(a, b, c);
}

// 递归调用
// 一个函数直接或者间接的调用自身
// 递归的终止条件（退出条件）
void c(void)
{
    printf("[%s] c begin.\n", __FUNCTION__);
    printf("[%s] end c.\n", __FUNCTION__);
}

void b(void)
{
    printf("[%s] b begin.\n", __FUNCTION__);
    printf("[%s] call c().\n", __FUNCTION__);
    c();
    printf("[%s] c() returned..\n", __FUNCTION__);
    printf("[%s] end b.\n", __FUNCTION__);
}

void a(void)
{
    printf("[%s] a begin.\n", __FUNCTION__);
    printf("[%s] call b().\n", __FUNCTION__);
    b();
    printf("[%s] b() returned..\n", __FUNCTION__);
    printf("[%s] end a.\n", __FUNCTION__);
}

// 给一个数n，求阶乘
static long long factorial(long n)
{
    if (n < 0) {
        return -1;
    }
    if ((n == 1) || (n == 1)) {
        return 1;
    }
    return n * factorial(n - 1);
}

// 适合用递归解决的问题
// 斐波那契数列
// 汉诺塔
// 二叉树结构
// 所有可以将大规模问题转化为同类小规模问题的解法

// 函数与数组例子
// 在形参的位置，一个 * 等价于一个 []
// static void print_array(int arr[], int n)
static void print_array(int *arr, int n)
{
    printf("size of arr = %lu.\n", sizeof(arr));
    // 数组作为入参会退化为指针
    for (int i = 0; i < n; i++) {
        printf("%d\n", *(arr + i));
    }
}

// 函数与一维数组 数组逆序
static void array_reverse(int *arr, int n)
{
    int tmp = 0;
    for (int i = 0, j = n - 1; i < j; i++, j--) {
        tmp = *(arr + i);
        *(arr + i) = *(arr + j);
        *(arr + j) = tmp;
    }
}

// 函数与二维数组
/*
二维数组传参
int a[M][N] = {...}
int *p = *a;
int (*q)[N] = a;

->  a[i][j]     *(a + i) + j    a[i] + j    p[i]    *p      q[i][j]     *q          q           p + 3   q + 2
    int n       int *n          int *n      int n   int n   int n       int *n      int(*)[N]   int *   int (*)[N]
*/
#define M 3
#define N 4

// static void print_2d_arr(int **a, int row, int col)
// {
//     int *p = (int **)a;
//     for (int i = 0; i < row; i++) {
//         for (int j = 0; j < col; j++) {
//             printf("a[%d][%d] = %d\n", i, j, *(p + i * N + j));
//         }
//     }
// }
// 二维数组的行列指针

static void print_2d_arr_2(int (*p)[N], int row, int col)
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            printf("a[%d][%d] = %d\n", i, j, *(*(p + i) + j));
        }
    }
}

static void print_2d_arr_3(int *p, int row, int col)
{
    for (int i = 0; i < row * col; i++) {
        printf("%d\n", p[i]);
    }
}

// 三个学生四门功课，求总平均分，查看某个学生的成绩
static float average_score(int *a, int num_stu, int num_les)
{
    int sum = 0;
    for (int i = 0; i < num_stu * num_les; i++) {
        sum += a[i];
    }
    return (float)sum / (num_stu * num_les);
}

int *find_num(int (*p)[N], int num)
{
    return (p + num);
}

// 函数与字符数组 实现 strcpy
// my_strcpy
char *my_strcpy(char *dest, size_t dest_size, const char *src, size_t src_size)
{
    int i = 0;
    if (dest_size < src_size) {
        return NULL;
    }
    for (; i < src_size; i++) {
        dest[i] = src[i];
    }
    dest[i] = 0;
    return dest;
}

// 函数指针
int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int main(int argc, char *argv[])
{
    // int i = 3;
    // int j = 5;
    // print_val(i, j);
    // swap(&i, &j);
    // printf("i = %d, j = %d\n", i, j);
    // printf("hello!\n");
    // printf("argc = %d\n", argc);

    // for (int i = 0; argv[i] != NULL; i++) {
    //     printf("%s\n", argv[i]);
    // }
    // printf("i = %d\n", i);

    // printf("============\n");
    // int a = 10, b = 100, c = 20;
    // printf("dist = %d\n", dist(a, b, c));

    // printf("============\n");   //递归调用
    // printf("[%s] begin.\n", __FUNCTION__);
    // printf("[%s] call a().\n", __FUNCTION__);

    // a();

    // printf("[%s] a() returned..\n", __FUNCTION__);
    // printf("[%s] end.\n", __FUNCTION__);

    // 阶乘
    // long n = 0;
    // printf("输入n：");
    // scanf("%ld", &n);
    // printf("%ld 的阶乘是 %lld\n", n, factorial(n));

    // // 函数与数组
    // int arr[] = {1, 3, 5, 7, 9};
    // int n = sizeof(arr) / sizeof(arr[0]);
    // printf("sizeof arr = %lu.\n", sizeof(arr) / sizeof(arr[0]));
    // print_array(arr, n);

    // // 数组逆序
    // for (int i = 0; i < n; i++) {
    //     printf("%d\n", *(arr + i));
    // }

    // array_reverse(arr, n);

    // for (int i = 0; i < n; i++) {
    //     printf("%d\n", *(arr + i));
    // }

    // // 函数与二维数组
    // int a[M][N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    // // print_2d_arr(a, M, N);
    // print_2d_arr_2(a, M, N);
    // print_2d_arr_3(a, M, N);
    // printf("average score = %0.3f\n", average_score(a, M, N));

    // int num = 2;
    // int *b = find_num(a, num);
    // for (int i = 0; i < N; i++) {
    //     printf("a[1][%d] = %d\n", num, b[i]);
    // }

    // // my_strcpy
    // char str1[] = "scotty checkout out this morning.";
    // char str2[128] = {0};
    // char *ret = my_strcpy(str2, sizeof(str2), str1, sizeof(str1));
    // printf("str2 = %s\n", str2);
    // printf("ret = %p\n", ret);
    // printf("str2 = %p\n", str2);

    // 函数指针
    int a= 3;
    int b = 5;
    int ret = 0;
    int (*p)(int, int);
    p = add;

    // ret = add(a, b);
    ret = p(a, b);
    printf("%d\n", ret);

    p = sub;
    ret = p(a, b);
    printf("%d\n", ret);

    // 函数指针数组
    int (*funcs[2])(int, int) = {add, sub};
    for (int i = 0; i < 2; i++) {
        printf("%d\n", funcs[i](a, b));
    }

    // 在linux 系统开发课程上介绍 exit(0) 和return 0 的区别
    exit(0);
    // 一个进程的返回状态，是给它的父进程看的
}

