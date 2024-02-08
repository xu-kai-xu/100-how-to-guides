#include <stdio.h>

// 回调函数的定义
void callback_function(int value) {
    printf("Callback function called with value: %d\n", value);
}

// 包含回调函数的函数
void perform_operation(void (*callback)(int), int value) {
    // 执行某些操作
    printf("Performing operation...\n");

    // 调用回调函数
    callback(value);
}

int main() {
    int data = 42;

    // 调用函数，传递回调函数作为参数
    perform_operation(callback_function, data);

    return 0;
}
