/*
# 八 构造类型

## 一、结构体
1. 产生及意义
    不同类型数据构成一个数据结构类型

2. 类型描述
    struct 结构体名{
        数据类型 成员1;
        数据类型 成员2；
        ...
    };

    匿名结构体

    结构体类型描述不占存储空间

3. 嵌套定义

4. 定义变量（变量、数组、指针），初始化及成员引用
    结构体定义通常放在声明和定义的位置，放在函数外
    成员引用：变量名.成员名
             指针->成员名
             (*指针).成员名
5. 结构体在内存当中占的空间大小

6. 函数传参（值，地址)
    值传参时，开销更大

## 二、共用体
1. 产生及意义
    结构体：成员共存，根据成员声明的顺序进行存储分配
    共用体：同一时刻只有一个成员生效，不同成员不能同时占用空间

2. 类型描述
    union 共用体名 {
        数据类型1 成员名1;
        数据类型2 成员名2;
        ...
    };

3. 共用体嵌套定义使用

4. 定义不同类型的变量（变量 数组 指针）、初始化及成员引用
    成员引用：变量名.成员名
             指针名->成员名

5. 共用体占用内存大小
    同一时刻只有一个成员可以合法访问

6. 函数传参的问题（值传递、地址传递）

7. 位域

三 枚举类型

1. 有限的情况、数量

2. 集合

根据所赋予的情况，顺次排列所有数值

3. 定义
    enum 标识符 {
        enum1,
        enum2,
        ...
        enum_n
    };

    enum 标识符 {
        enum1 = 0,
        enum2,
        ...
        enum_n
    };
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define NAME_SIZE 32

struct simp_st {
    int i, j;
    float f;
    char ch;
};

// struct simp_st {
//     int i, j;
//     float f;
//     char ch;
// }__attribute__((packed));   // 网络编程，指定不对齐

struct birthday_st {
    int year;
    int month;
    int day;
};

struct student_st_1 {
    int id;
    char name[NAME_SIZE];
    struct birthday_st birth;   // 嵌套
    int math;
    int chinese;
};

void func(struct simp_st b)
{
    printf("%lu\n", sizeof(b));
}

void func_2(struct simp_st *c)
{
    printf("sizeof *c = %lu\n", sizeof(*c));
    printf("sizeof c = %lu\n", sizeof(c));
}

// // 没有名字的结构体，无头结构体
// struct {
//     int i;
//     char ch;
//     float f;
// }a = {1, 'a', 3.14}, b = {2, 'b', 6.28};

// 有关student的管理
#define NAME_MAX 1024
struct student_st {
    int id;
    char *name;
    int math;
    int chinese;
};

void stu_set(struct student_st *p, const struct student_st *q)
{
    // strcpy(p->name, "Alan");
    // p->math = 101;
    // p->chinese = 110;
    // *p = *q;
    p->id = q->id;
    p->name = malloc(strlen(q->name) + 1);
    if (p->name == NULL) {
        exit(1);
    }
    strcpy(p->name, q->name);
    p->math = q->math;
    p->chinese = q->chinese;
}

void stu_show(struct student_st *p)
{
    printf("%d %s %d %d\n", p->id, p->name, p->math, p->chinese);
}

void stu_change_name(struct student_st *p, char *new_name)
{
    free(p->name);
    p->name = malloc(strlen(new_name) + 1);
    strcpy(p->name, new_name);
}

void menu(void)
{
    printf("\n1 set.\n2 change name\n3 show info\n\n");
    printf("enter your choice: ");
}

// 共用体定义
union test_un
{
    int i;
    float f;
    double d;
    char ch;
};

static void test_union()
{
    // 共用体同一时刻只有一个成员是有效的
    union test_un a;
    union test_un *p = &a;
    a.f = 3.14;
    printf("sizeof a = %lu\n", sizeof(a));
    printf("%f\n", a.f);
    printf("%f\n", a.d);    // 无效操作
}

// 结构体嵌套共用体
struct struct_un {
    int i;
    char ch;
    union {
        int a;
        char c;
    }un;
    float f;
};

// 共用体嵌套结构体
union un_struct {
    int a;
    double d;
    struct {
        int arr[10];
        float f;
    }c;
};

// 共用体结构体嵌套的用法
// 大端序 小端序存储
// 需求：32位的无符号数，求它高16位和低16位相加是多少
static void sum_demo()
{
    unsigned int i = 0x11223344;
    printf("%x\n", (i >> 16) + (i & 0xFFFF));
}

union {
    struct {
        uint16_t i;
        uint16_t j;
    } x;
    uint32_t y;
} a;

static void sum_demo_2()
{
    a.y = 0x11223344;
    printf("%x\n", a.x.i + a.x.j);
}

// 位域
union {
    struct {
        char a: 1;  // 占一个位
        char b: 2;  // 占2个位
        char c: 1;
    } x;
    char y;
} w;

static void bit_field()
{
    // w.y = 1;
    w.y = 4;
    // w.y = 6;
    printf("sizeof w = %lu\n", sizeof(w));
    printf("w.x.a = %d\n", w.x.a);
    printf("w.x.b = %d\n", w.x.b);
    printf("w.x.c = %d\n", w.x.c);
}

// 枚举类型
enum day {
    MON = 1,
    TUS,
    WES,
    THR,
    FRI,
    SAT,
    SAU
};

int main()
{
    // // 定义公式模板： type name = value；
    // struct simp_st a;
    // printf("size of simp_st before init: %lu\n", sizeof(a)); // 定义后 初始化前求大小

    // struct simp_st a = {123, 456, 789.113, 'x'};
    // a.i = 112233;
    // printf("%d, %d, %f, %c\n", a.i, a.j, a.f, a.ch);

    // // 嵌套定义和引用
    // struct student_st stu = {10011, "Alan", {2014, 5,23}, 90, 101};

    // printf("%d %s %d %d %d %d %d\n", stu.id, stu.name, stu.birth.year, stu.birth.month, stu.birth.day, stu.math, stu.chinese);

    // // 部分初始化
    // struct student_st stu1 = {.math = 101, .chinese = 102};
    // printf("%d %s %d %d %d %d %d\n", stu1.id, stu1.name, stu1.birth.year, stu1.birth.month, stu1.birth.day, stu1.math, stu1.chinese);

    // // 定义指向结构体指针
    // struct student_st *p = &stu;
    // p->id = 315015;
    // printf("%d %s %d %d %d %d %d\n", p->id, p->name, p->birth.year, p->birth.month, p->birth.day, p->math, stu.chinese);

    // struct student_st arr[2] = {stu, stu1};

    // struct simp_st a;
    // struct simp_st *p = &a;
    // printf("sizeof a = %lu\n", sizeof(a));
    // printf("sizeof p = %lu\n", sizeof(p));
    // printf("sizeof int = %lu\n", sizeof(int));
    // printf("sizeof float = %lu\n", sizeof(float));

    // func(a);
    // func_2(p);

    // 没有名字的结构体

#if 1
    // 有关student的管理
    struct student_st stu;
    struct student_st src;
    char newname[NAME_SIZE] = {0};
    int choice = 0;
    do {
        menu();
        int ret = scanf("%d", &choice);
        if (ret != 1) {
            break;
        }
        switch(choice) {
            case 1:
                src.name = malloc(sizeof(char) * NAME_MAX);
                printf("enter the new stu's info:\n");
                scanf("%d%s%d%d", &(src.id), src.name, &(src.math), &(src.chinese));
                stu_set(&stu, &src);
                break;
            case 2:
                printf("输入新名字:\n");
                scanf("%s", newname);
                stu_change_name(&stu, newname);
                break;
            case 3:
                stu_show(&stu);
                break;
            default:
                exit(1);
        }
        sleep(1);
    } while(1);
#endif

    // test_union();
    // sum_demo();
    // sum_demo_2();
    // bit_field();

    // // 枚举类型
    // enum day day_1 = MON;
    // enum day day_5 = FRI;
    // printf("%d\n", day_1);
    // printf("%lu\n", sizeof(day_1));
    // printf("%d\n", day_5);

    return 0;
}