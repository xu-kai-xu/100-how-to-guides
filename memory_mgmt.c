/*
九 动态内存管理

auto    编译器默认分配，在栈上
static  静态区
动态内存管理    从堆上手动分配

原则：谁申请 谁释放，防止产生内存泄漏
申请后忘记释放的空间，会随着进程结束而被释放掉
对于进程运行很长时间的程序，积累的没有释放的内存会很可怕
把自己的屁股擦干净

最好的办法，让malloc和free出现在同一个函数当中，
至少要出现在同一个模块当中。



1. malloc   void *malloc(size_t size);
2. calloc   void *calloc(size_t nmemb, size_t size);
3. realloc  void *realloc(void *ptr, size_t size);  // 在原始空间的基础重新申请固定大小的空间
4. free     void free(void *ptr);

void * 和函数指针类型之间转换，能不能用等号直接赋值，属于未定义行为。

*/

#include <stdlib.h>
#include <stdio.h>

static void malloc_demo()
{
    int *p = NULL;
    // p = (int *)malloc(sizeof(int) * 1);
    p = malloc(sizeof(int) * 1);
    if (p == NULL) {
        printf("malloc error!\n");
        exit(1);
    }
    // *p = 6666666666666666;
    *p = 666666;
    printf("%p -> %d\n", p, *p);

    free(p);

    // *p = 123;
    printf("%p -> %d\n", p, *p);
    // p = NULL;
}

static void func(int *p, int n)
{
    p = malloc(n);  // 这是一个没有安全释放的例子
    if (p == NULL) {
        exit(1);
    }
    return;
}

static void test()
{
    int *p = NULL;
    int n = 100;
    func(p, 100);
    free(p);
}

static void test_mem_ask()
{
    int *p = NULL;

    p = malloc(1024L * 1024L * 1024L * 8L);
    printf("%lu\n", sizeof(p));
    free(p);
    p = NULL;
}

int main()
{
    // malloc_demo();
    // test();

#if 0
    int *p = NULL;
    p = malloc(sizeof(int) * 1);
    if (p == NULL) {
        printf("malloc error!\n");
        exit(1);
    }
    // *p = 6666666666666666;
    *p = 666666;
    printf("%p -> %d\n", p, *p);

    free(p);
    p = NULL;   // 保护指针不被胡乱使用 错误使用

    *p = 123;    // 野指针
    printf("%p -> %d\n", p, *p);
#endif

    // 测试能够申请的最大内存
    test_mem_ask();

    exit(0);
}