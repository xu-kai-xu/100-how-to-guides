#include <pthread.h>
#include <stdio.h>

// 线程函数定义
void *print_hello(void *data)
{
    printf("hello from new thread - got %s\n", data);
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread_id = 0;
    char data[] = "scotty checkedout this morning.";

    // 创建新线程
    if (pthread_create(&thread_id, NULL, print_hello, (void *)data)) {
        printf("error creating thread.");
        return 1;
    }

    // 等待线程结束
    if (pthread_join(thread_id, NULL)) {
        printf("error joinint thread.");
        return 2;
    }

    printf("thread_id = %u\n", thread_id);

    return 0;
}