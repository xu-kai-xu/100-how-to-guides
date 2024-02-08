// 选择和循环部分的练习题
#include <stdio.h>
#include <stdlib.h>

/* 第一题
投资问题：
a 以每年10%的单利息投资了100美元，
b 以每年5%的复合利息投资了100美元，
编写一个程序，计算需要多少年，b的投资总额才会超过a的，
并且显示出到那个时刻为止，两个人的资产总额。
*/
static void test1(void)
{
    float a = 100, b = 100;
    int i = 0;  // 起始为0年，即当前

    while(a >= b) {
        a = a + 0.1 * 100;
        b = b * (1 + 0.05);
        i++;
        printf("第%d年，a = %3f, b = %3f.\n", i, a, b);
    }

    printf("需要%d年，a = %3f, b = %3f.\n", i, a, b);

}

/* 第二题
终终端读入数据，直到输入0值为止，
计算出其中的偶数的个数及平均值，
和奇数的个数和平均值。
*/
static void test2(void)
{
    int sum_even = 0;
    int count_even = 0;
    int sum_odd = 0;
    int count_odd = 0;
    int num = 0;

    while (1) {
        printf("input an integer (input 0 if you want to exit): ");
        scanf("%d", &num);
        if (num == 0) {
            break;
        }
        if (num % 2 == 0) {
            sum_even += num;
            count_even++;
        } else {
            sum_odd += num;
            count_odd++;
        }
    }

    printf("the average of even numbers is: %d.\n", sum_even / count_even);
    printf("the average of odd numbers is: %d.\n", sum_odd / count_odd);
}


/* 第三题
终终端输入若干字符，对其中的元音字母进行统计,
*/
#define STR_LEN 200
static void test3(void)
{
    char str[STR_LEN] = {0};
    char vowel[5] = {'a', 'e', 'i', 'o', 'u'};
    int count[5] = {0};
    printf("input some chars: ");
    fgets(str, 199, stdin);

    for (int i = 0; i < STR_LEN; i++) {
        switch (str[i]) {
            case 'a':
                count[0]++;
                break;
            case 'e':
                count[1]++;
                break;
            case 'i':
                count[2]++;
                break;
            case 'o':
                count[3]++;
                break;
            case 'u':
                count[4]++;
                break;
            default:
                break;
        }
    }
    for (int i = 0; i < 5; i++) {
        printf("%c: %d\n", vowel[i], count[i]);
    }
}

/* 第四题
 fibonacci 数列的前40项，不能用数组实现。
*/
static void test4()
{
    int count_1 = 1;
    int count_2 = 2;
    int fib = 0;
    int temp = 0;

    printf("fib[1] = %d\n", 1);
    printf("fib[2] = %d\n", 2);

    for (int i = 3; i <= 40; i++) {
        fib = count_1 + count_2;
        printf("fib[%d] = %d\n", i, fib);
        count_1 = count_2;
        count_2 = fib;
    }

}


/* 第五题
输出一个九九乘法表
【嵌套循环】
*/

/* 第六题
百钱买百鸡，鸡翁一，值钱五，鸡母一，值钱三，
三鸡雏，值钱一，百钱买百鸡
问，鸡翁 鸡母 鸡雏 各几只
*/
static void test6(void)
{
    // 百钱买百鸡
    int x = 0, y = 0, z = 0;
    int left = 0;

    for (x = 0; x <= 100 / 5; x++) {
        printf("x = %d\n", x);
        for (y = 0; y <= (100 - 5 * x) / 3; y++) {
            left = 100 - 5 * x - 3 * y;
            z = left * 3;

            if (x + y + z == 100) {
                printf("鸡翁：%d，鸡母：%d，鸡雏：%d。\n", x, y, z);
            }
        }
    }
}


/* 第七题
求出1000以内的水仙花数：
水仙花数：153 = 1^3 + 5^3 + 3^3
*/
int flower_sum(int n){
    int sum = 0;
    int m = n;
    int tmp = 0;

    while (m / 10) {
        tmp = m % 10;
        sum += tmp * tmp * tmp;
        m = m / 10;
    }

    sum += m * m * m;
    if (sum == n) {
        return n;
    } else {
        return -1;
    }
}

static void test7(void)
{
    int res = 0;
    for (int i = 0; i <= 1000; i++) {
        res = flower_sum(i);
        if (res == -1) {
            continue;
        } else {
            printf("%d\n", res);
        }
    }
}

/* 第八题
1000以内所有的质数
*/
// 筛法求质数
static void test8(void)
{
    int array[1001] = {0};  // 1-1000
    array[0] = 1;  // 0 不是质数
    array[1] = 1;  // 1 不是质数
    for (int i = 2; i <= 1000; i++) {
        if (array[i] == 0) { // 说明是质数
            int j = i + i;
            while (j <= 1000) {
                array[j] = 1;
                j += i;
            }
        }
    }

    for (int k = 0; k <= 1000; k++) {
        if (array[k] == 0) {
            printf("%d\n", k);
        }
    }
}

/* 第九题
在终端上实现如下输出
ABCDEF
BCDEF
CDEF
DEF
EF
F
*/
#include <string.h>
static void test9()
{
    char strs[] = "ABCDEF";
    int start = 0;
    int end = strlen(strs);
    for (start; start < end; start++) {
        printf("%s\n", strs + start);
    }
}



/* 第十题 钻石形
https://blog.csdn.net/howard2005/article/details/79409408
输入一个奇数，输出对应的钻石形
*/
static void print_stars(int n, int m)
{
    // n表示这一行有多少颗星星，m表示这一行有多少空格
    for (int j = 0; j < m; j++) {
        printf(" ");
    }
    for (int i = 0; i < n; i++) {
        printf("*");
    }
    printf("\n");
}

static void test10(int n)
{
    // n 表示行数，也表示最长的行有多少颗星星
    if (n % 2 == 0) {
        printf("n must be odd number!\n");
        return;
    }

    int space = (n - 1) / 2;
    for (int i = 1; i <=n;) {
        print_stars(i, space);
        i += 2;
        space -= 1;
    }
    space++;
    for (int j = n - 2; j >=1;) {
        print_stars(j, ++space);
        j -= 2;
    }
}


/* 十一题
从终端输入n个数，以字母q或Q为终止标志，求和。
*/
static void test11()
{
    int sum = 0;
    char c[20] = {0};
    printf("请输入一些数字，以q或Q为终止标志：\n");
    while (1) {
        scanf("%s", c);
        if (*c == 'q' || *c == 'Q') {
            break;
        }
        sum += atoi(c);
        printf("num = %d\n", atoi(c));
    }
    printf("sum = %d\n", sum);
}

/* 十二题
从半径为1开始，输出圆的面积，直到面积大于100为止。
*/
static void test12()
{
    float area = 0;
    int r = 1;
    while (area <= 100) {
        area  = 3.14 * r * r;
        printf("area = %f\n", area);
        r += 1;
    }
}


int main()
{
    // test1();
    // test2();
    // test3();
    test4();
    // test6();
    // test7();
    // test8();
    // test9();
    // test10(11);
    // test11();
    // test12();

    exit(0);
}