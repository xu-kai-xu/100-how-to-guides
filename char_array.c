/*
字符数组

1. 定义 初始化 存储特点

存储类型 数据类型 标识符[下标]

初始化：
1）单个字符初始化
2）字符串常量初始化
3）

2. 输入输出

3. 常用函数

4. 多维数组


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10

/*
strlen & sizeof
strcpy & strncpy
strcat & strnct
strcmp & strncmp
*/

int string_opt(void)
{
    //strlen 计算字符串长度，不包括尾0，遇到尾0，strlen就结束了
    //sizeof 计算字符串在内存中真正占用的字节数
    char str[32] = "hello\0abc";
    // printf("%u\n%u\n", strlen(str), sizeof(str));

    // strcpy(str, "abcde scotty checked out this");  //写入长度超过可容纳长度会报错
    // puts(str);
    // strcpy(str, "abcde");
    // puts(str);
    strncpy(str, "abcde123456", 10);
    puts(str);

    strcat(str, "hahaha");
    strcat(str, " world");
    puts(str);

    // str[32] = ""; // 不能直接赋值为0
    memset(str, 0, sizeof(str));
    strncat(str, "hahahaha", 31);
    strncat(str, " hahahaha", 31);
    puts(str);

    // strcmp 比的是字符串的ascii码，逐字符比较
    char str1[32] = "mmhello";
    char str2[32] = "mmworld";
    printf("%d\n", strcmp(str1, str2));
    printf("%d\n", strncmp(str1, str2, 2));
}


/*
单词计数
统计一串字符串中的单词个数

分隔符后面是字母，说明是一个新的单词

*/
static void count_word(void) {
    char str[128];
    int count = 0;
    int flag = 0;

    gets(str);

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            flag = 0;
        } else { // str[i] is a char
            if (flag == 0) {
                count++;
                flag = 1;
            }
        }
    }

    printf("count = %d\n", count);
}

static void count_word_2(void) {
    char str[128];
    int count = 0;

    gets(str);

    if (str[0] != ' ') {
        count++;
    }

    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i - 1] == ' ' && str[i] != ' ') {
            count++;
        }
    }

    printf("count = %d\n", count);
}

static void multi_array(void)
{
    int a[2][3][4];

}

int main()
{
    // char str1[N] = {'a', 'b', 'c'}; //  单个字符初始化

    // for (int i = 0; i < N; i++) {
    //     printf("%c", str1[i]);
    // }
    // printf("\n");

    // char str2[N] = "abcd";
    // printf("%s\n", str2);

    // char str3[N] = "abcdfghijklmn";
    // printf("%s\n", str3);

    // gets(str3);
    // puts(str3);
    // printf("%s\n", str3);

    // scanf("%s", str3);  // 不能获得带有空格的字符串，回车 、空格都是作为当前输入的结束
    // printf("%s\n", str3);

    // char str1[N], str2[N], str3[N];

    // scanf("%s%s%s", str1, str2, str3);
    // printf("%s\n%s\n%s\n", str1, str2, str3);

    // printf("%s\n", str3);
    // string_opt();

    // count_word();
    // count_word_2();
}