/*
指针

1. 变量与地址的关系
    变量：用户对某一块内存空间的抽象表示。
    地址：指针等价于地址。

2. 指针 & 指针变量
    指针是常量，
    指针变量用于存储指针。
    变量类型：在这个变量所占用的空间里存放的是什么类型的数据。

    //指针在某一个平台上所占的空间是固定的大小，
    指定指针类型只是为了从这个地址偏移一定的长度。
    偏移的长度与变量类型有关。

3. 直接访问 & 间接访问
    通过变量名直接访问变量的值
    通过变量所在的地址访问变量的值，


4. 空指针 & 野指针

5. 空类型的指针

6. 定义 初始化 书写规则

7. 指针运算
    取地址：&变量（值）的地址
    取值： *地址存放的值

    关系运算：两个指针比较大小，比的是两个指针所指向地址的高低

    ++，--  改变当前指针所指向的位置

8. 指针与数组的关系
    指针与一维数组
        一维数组名就是一个地址
        一维数组名与它对应的指针变量在查找数组元素时可以互换
        一维数组名是常量，不能赋值；它对应的指针变量是个变量，可以赋为别的地址值

    指针与二维数组
        二维数组输入输出的关系
        二维数组的行列地址：
            理解为一维地址，二维地址更好些



    指针与字符数组
    指针与多维数组

9. 指针常量 & 常量指针
    const 与指针，例如 `fopen`，`memcpy`


10. 指针数组 & 数组指针
    数组指针：指向数组的指针
        定义方式：[存储类型] 数据类型 (*指针名)[下标] = value
                int (*p)[3] = NULL; 指向一个 int [3] 类型的指针，指向一个具有三个整型元素的存储空间的首地址

    指针数组：是一个数组
        [存储类型] 数据类型 *数组名[长度]
                    int *arr[3]

11. 多级指针



*/

#include <stdio.h>
#include <stdlib.h>

#if 0
static void demo_1(void)
{
    int i = 1;
    int *p = &i;
    int **q = &p;
    float *qt = &i; // 指针在某一个平台上所占的空间是固定的大小
    double *d = &i;
    char *c = &i;
    // TYPE NAME = VALUE;
    // int* p = &i;   //这里的类型不是int，而是 int*

    printf("i = %d\n", i);
    printf("&i = %p\n", &i);
    printf("p = %p\n", p);
    printf("&p = %p\n", &p);
    printf("*p = %d\n", *p);
    printf("\n");

    printf("sizeof i = %lu\n", sizeof(i));
    printf("sizeof p = %lu\n", sizeof(p));
    printf("sizeof qt = %lu\n", sizeof(qt));
    printf("sizeof d = %lu\n", sizeof(d));
    printf("sizeof c = %lu\n", sizeof(c));
    printf("\n");

    printf("*p = %d\n", *p);
    printf("*qt = %f\n", *qt);
    printf("*d = %f\n", *d);
    printf("*c = %c\n", *c);

    printf("*q = %p\n", *q);
    printf("**q = %d\n", **q);
}
#endif

// 指针初始化为空，是为了避免野指针
// 野指针：当前指针指向不确定，或者未指向任何地方，而直接使用了
static void pointer_init(void)
{
    int *p = NULL;
    // printf("%p --> %d\n", p, *p); // 执行后出现段错误
    // printf("%d\n", *p);  // 执行后出现段错误
    printf("%p\n", p); // 结果为 nil
}

static void pointer_test(void)
{
    int *p;
    *p = 1; // 会报段错误  指针没有指向合法地址
    printf("%d\n", *p);
}

static void pointer_type(void)
{
    // 空类型的指针
    //  任何类型的指针值，都能够赋值给void*
    //  void* 可以把自己的值赋值给任何指针类型
    void *q = NULL;
}

static void pointer_def(void)
{
    // 定义与初始化
}

/*
指针变量与一维数组名的区别：
指针变量是个变量，他的值可变。
一维数组名是常量，它的值不能改变。
*/
static void pointer_and_oneD_array(void)
{
    int a[3] = {1, 2, 3};
    int *p = a;

    printf("%p, %p\n", a, a + 1);
    printf("%p, %p\n", p, p + 1);

    // a++;    // 数组名是常量，不可修改，此处会报错  lvalue required as increment operand
    // p++;    // 指向下一个同类型的元素

    for (int i = 0; i < sizeof(a) / sizeof(*a); i++) {
        printf("%p -> %d\n", a + i, a[i]);
        printf("%p -> %d\n", p + i, a[i]);
        printf("%p -> %d\n", p + i, p[i]);
        printf("%p -> %d\n", p + i, *(p + i));
    }
    printf("\n");

    // 指针与数组名的大小不同
    // 数组名的大小表示整个数组的大小
    // 指针变量的大小固定为8
    printf("sizeof(a) = %lu\n", sizeof(a));
    printf("sizeof(p) = %lu\n", sizeof(p));
}

static void pointer_and_oneD_array_2(void)
{
    int a[3];
    int *p = a;

    for (int i = 0; i < sizeof(a) / sizeof(*a); i++) {
        printf("%p -> %d\n", &a[i], a[i]);
    }

    for (int i = 0; i < sizeof(a) / sizeof(*a); i++) {
        // scanf("%d", &a[i]);
        // scanf("%d", &p[i]);
        // scanf("%d", p + i);
        scanf("%d", p++);
    }

    // p = a;
    for (int i = 0; i < sizeof(a) / sizeof(*a); i++, p++) {
        // printf("%p -> %d\n", &a[i], a[i]);
        printf("%p -> %d\n", p, *p);
    }
    printf("\n");

}

static void pointer_and_oneD_array_3(void)
{
    int *p = (int [3]){1, 2, 3};  // 奇技淫巧

    for (int i = 0; i < 3; i++) {
        // for 循环里的i，其生命周期只在for循环里
        printf("%p -> %d\n", &p[i], p[i]);
    }
    // printf("%d\n", i);
}

static void test(void)
{
    int a[] = {5, 1, 7, 2, 8, 3};
    int *p = &a[1];

    // int y = (*--p)++;  // 5
    int y = ++(*--p);  // 6
    printf("y = %d\n", y);
}

#if 0
static void twoD_io()
{
    int a[2][3] = {1, 2, 3, 4, 5, 6};
    int *p = a; // 类型为整型，所以每次偏移为一个整型的大小，会有warning


    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%p -> %d\n", &a[i][j], a[i][j]);
        }
    }

    for (int i = 0; i < 6; i++) {
            printf("%p -> %d\n", p + i, *(p + i));
    }
}
#endif

/*

在 C 语言中，二维数组可以被看作是一维数组的数组。对于 int a[2][3] = {1, 2, 3, 4, 5, 6};，a 是一个包含两个元素的数组，其中每个元素都是一个包含三个 int 的数组。

现在，让我们看看 (a + i) 和 *(a + i)。

(a + i)：这是一个指向 int 数组的指针，它指向二维数组的第 i 行。在这里，a 是一个指向包含三个 int 的数组的指针，即 int(*)[3]。当你对 a 加上 i，你得到的是一个新的指针，它指向二维数组的第 i 行。因此，(a + i) 的类型是 int(*)[3]。

*(a + i)：这是对 (a + i) 指针的解引用。当你对一个指向 int 数组的指针进行解引用，你得到的是一个 int 数组。在大多数情况下，数组会自动转换为指向其第一个元素的指针，因此 *(a + i) 的结果是一个指向第 i 行的第一个元素的指针，即 int*。换句话说，*(a + i) 等同于 a[i]。

所以，a + i 和 *(a + i) 的主要区别在于它们的类型和它们所指向的内容：a + i 是一个指向 int 数组的指针，而 *(a + i) 是一个 int 指针。
*/
static void pointer_row_col(void)
{
    int a[2][3] = {1, 2, 3, 4, 5, 6};
    // int *p = a; // 类型为整型，所以每次偏移为一个整型的大小，会有warning
    // int *p = *(a + 0);  //对行地址取 * ，会把它降级成列地址
    int *p = &a[0][0];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%p -> %d\n", *(a + i) + j, *(*(a + i) + j));
        }
    }

    printf("\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("a + %d = %p -> %p \n", i, (a + i), *(a + i));
        }
    }
    printf("\n");

    for (int i = 0; i < 6; i++) {
            printf("%p -> %d\n", p + i, *(p + i));
    }
    printf("\n");

    for (int i = 0; i < 6; i++, p++) {
            printf("%p -> %d\n", p , *p);
    }
}

static void array_pointer(void)
{
    int a[2][3] = {1, 2, 3, 4, 5, 6};
    int (*p)[3] = a;

    printf("%p -> %p\n", a, a + 1);
    printf("%p -> %p\n", p, p + 1);
    printf("\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%p -> %d\n", *(a + i) + j, *(*(a + i) + j));
        }
    }
    printf("\n");

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%p -> %d\n", *(p + i) + j, *(*(p + i) + j));
        }
    }
}

/*
指针和字符数组使用的区别
1.
*/
static void pointer_char_array(void)
{
    char str[] = "i love china!";
    puts(str);

    char *p = str + 7;
    puts(p);
}

#include <string.h>
static void pointer_char_array_2(void)
{
    char str[] = "hello";
    printf("size of str = %lu, strlen str = %lu\n", sizeof(str), strlen(str));
    // str = "world";  // 会报错，str是个地址常量，无法复制
    strcpy(str, "world");
    puts(str);
}

static void pointer_char_array_3(void)
{
    char *str = "hello";
    printf("size of str = %lu, strlen str = %lu\n", sizeof(str), strlen(str));
    // sizeof 包括了结尾的0
    // strcpy(str, "world");   //会报错
    str = "world";
    puts(str);
}

/*
变量常量化
const int a;
int const a;

常量指针
const int *p;   // 指针可以发生变化，指针指向的内容不能变
int const *p;

指针常量
int *const p;   // 指针的指向永远不能变化，但指针指向的内容可以变化
【先看到const，就先念常量；先看到*，就先念指针】
【const 后面加指针，说明指针的值不能变；const后面跟目标（*p），目标不能变】

既是指针常量 又是常量指针
const int *const p;

const 的作用：
1. 把某些内容进行常量化【宏最大的缺点是 不检查语法】
#define PI 3.14
*/

static void const_demo()
{
    // float pi = 3.14;    // 用变量保存，pi的值随时可能被误改变
    const float pi = 3.14;  // const 修饰的变量，必须在定义时就初始化
    // pi = 3.1415926;
    printf("%f\n", pi);

    // float *p = &pi; //可以通过指针间接引用的方式改变const修饰的常量，会告警
    // *p = 3.1415926;
    // printf("pi = %f, *p = %f\n", pi, *p);
}

static void const_demo_2()
{
    // 常量指针
    int i = 1;
    int j = 100;
    const int *p = &i;

    printf("i = %d\n", *p);

    i = 2;  // 可以修改
    printf("i = %d\n", *p);

    // *p = 10;    //会报错，这是一个常量指针
    // printf("*p = %d\n", *p);

    p = &j;
    printf("*p = %d\n", *p);
}

// 指针常量
static void const_demo_3()
{
    int i = 1;
    int j = 100;
    int *const p = &i;

    printf("*p = i = %d\n", *p);

    *p = 10;

    printf("*p = %d\n", *p);

    // p = &j; //报错
}

static void const_demo_4()
{
    int i = 1;
    int j = 100;
    const int *const p = &i;    // 这样，指针和指针指向的值都不可改变

    printf("*p = i = %d\n", *p);

    // *p = 10; // 报错
    i = 20;

    // p = &j; // 报错

    printf("*p = %d\n", *p);
}

static void array_of_pointer(void)
{
    //指针数组，由指针构成的数组
    char *name[5] = {"leeyy", "wdx", "caoxf", "halala", "wgujiji"};
    char *tmp = NULL;

    for (int i = 0; i < 5; i++) {
        printf("%s\n", name[i]);
    }
    printf("\n");
    // 快速排序法
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (strcmp(name[i], name[j]) > 0) {
                tmp = name[i];
                name[i] = name[j];
                name[j] = tmp;
            }
        }
    }
    printf("\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\n", name[i]);
    }
}

int main()
{
    // demo_1();
    // pointer_init();
    // pointer_test();
    // pointer_and_oneD_array();
    // pointer_and_oneD_array_2();
    // pointer_and_oneD_array_3();
    // test();
    // twoD_io();
    // pointer_row_col();
    // array_pointer();
    // pointer_char_array();
    // pointer_char_array_2();
    // pointer_char_array_3();
    // const_demo();
    // const_demo_2();
    // const_demo_3();
    // const_demo_4();
    array_of_pointer();
}