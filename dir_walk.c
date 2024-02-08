// 以非递归方式遍历目录，获取以txt为后缀的文件名

#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 5
#define MAX_PATH_LENGTH 200
#define FILE_NUM 10

struct Stack
{
    char *items[STACK_SIZE];
    int top;
};

struct Stack *createStack()
{
    struct Stack *stack = malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

int isFull(struct Stack *stack)
{
    return stack->top == STACK_SIZE - 1;
}

int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

void push(struct Stack *stack, const char *item)
{
    if (isFull(stack))
        return;
    stack->items[++stack->top] = strdup(item);
}

char *pop(struct Stack *stack)
{
    if (isEmpty(stack))
        return NULL;
    return stack->items[stack->top--];
}

void find_txt_files_non_recursive(char bcp_list[][MAX_PATH_LENGTH], const char *path, int *file_count)
{
    struct Stack *stack = createStack();
    push(stack, path);
    *file_count = 0;

    while (!isEmpty(stack))
    {
        char *currentPath = pop(stack);
        DIR *dir = opendir(currentPath);
        if (dir == NULL)
        {
            free(currentPath);
            continue;
        }

        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_DIR)
            {
                if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                    continue;
                }
                char newPath[MAX_PATH_LENGTH];
                snprintf(newPath, sizeof(newPath), "%s/%s", currentPath, entry->d_name);
                push(stack, newPath);
            }
            else
            {
                if (strstr(entry->d_name, ".txt"))
                {
                    // printf("%s/%s\n", currentPath, entry->d_name);
                    // 检查文件名是否合法
                    snprintf(bcp_list[(*file_count)++], MAX_PATH_LENGTH, "%s/%s", currentPath, entry->d_name);
                    if (*file_count >= FILE_NUM) {
                        return;
                    }
                }
            }
        }

        closedir(dir);
        free(currentPath);
    }

    free(stack);
}

int main()
{
    char bcp_list[FILE_NUM][MAX_PATH_LENGTH] = {0};
    char walk_dir[] = "/home/xukk/var/verona/sectel";
    int file_count = 0;
    find_txt_files_non_recursive(bcp_list, walk_dir, &file_count);

    for (int i = 0; i < file_count; i++) {
        printf("%s\n", bcp_list[i]);
    }
    return 0;
}
