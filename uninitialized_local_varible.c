#include <stdio.h>

struct score_st {
    int id;
    char name[32];
    int math;
    int chinese;
};

void uninitialized_variable() {
    int x;   // 未初始化的局部变量

    printf("Uninitialized variable: %d\n", x);  // 输出不确定的值
}

void uninitialized_struct()
{
    struct score_st tmp = {0};
    printf("%d, %s, %d, %d\n", tmp.id, tmp.name, tmp.math, tmp.chinese);
}

int main() {
    uninitialized_variable();
    uninitialized_struct();

    return 0;
}
