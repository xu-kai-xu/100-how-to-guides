/*
typedef: 为已有的数据类型改名
typedef 已有的数据类型 新名字;

typedef 与 宏定义的区别

#define INT int
typedef int INT;

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 32
#define NAME_MAX 1024

typedef int INT;
typedef int ARR[6];

struct node_st {
    int i;
    float f;
};

typedef struct node_st NODE;
typedef struct node_st *NODEP;

#if 0
// 函数
typedef int FUNC(int);  // int(int) FUNC;
FUNC f; // int f(int);

typedef int *FUNCP(int); // int *p(int);

// 函数指针
typedef int *(*FUNCP)(int);
FUNCP P; // int *(*p)(int);
#endif

// 学生管理系统的例子
typedef struct student_st {
    int id;
    char *name;
    int math;
    int chinese;
} STU;

void stu_set(STU *p, const STU *q)
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

void stu_show(STU *p)
{
    printf("%d %s %d %d\n", p->id, p->name, p->math, p->chinese);
}

void stu_change_name(STU *p, char *new_name)
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


int main()
{
    // INT i; // --> int i;
    // i = 100;
    // printf("%d\n", i);
    // 有关student的管理
    STU stu;
    STU src;
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
}

