#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    char path1[] = "../pylang/?>1";
    char path2[] = "../pylang/for_loop.py";

    char resolved_path[PATH_MAX] = {0};

    char *res1 = realpath(path1, resolved_path);

    if (res1) {
        printf("Original path: %s\n", path1);
        printf("Resolved path: %s\n", resolved_path);
    } else {
        perror("realpath");
        return 1;
    }
    return 0;

}