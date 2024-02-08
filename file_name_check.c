#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char prefix[4]; // 2 位
    char factory[20]; // 18位
    char timestamp[12]; // 10位
    char file_type[16];   // 16位
    char esn[16]; //
    char cpu_id[2]; // 一位
    char suffix[6]; // 5位
} sectel_wa_file_part_t;

// 检查字符串是否只包含字母
int isValid(const char *str) {

}

void check_filename(const char *filename) {
    // 创建一个副本，因为 strtok 函数会修改原始字符串
    char *filename_copy = strdup(filename);

    // 使用 "-" 作为分隔符分割字符串
    char *token = strtok(filename_copy, "-");

    while (token != NULL) {
        printf("token is %s\n", token);
        token = strtok(NULL, "-");
    }

    // 释放副本的内存
    free(filename_copy);
}

int main() {
    char file_name[] = "NS-97812345-1677894500-WA_Q01010002-BAR20230534-0-0.bcp";
    check_filename(file_name);
    return 0;
}
