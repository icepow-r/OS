#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct
{
    pthread_t id;
    int flag;
    char sym;
} thread_info;

void *proc1(void *arg)
{
    thread_info *ti = (thread_info *)arg;
    while (ti->flag == 0)
    {
        printf("%c", ti->sym);
        fflush(stdout);
        sleep(1);
    }
    int *result = calloc(1, sizeof(int));
    *result = 1;
    return (void *)result;
}

void *proc2(void *arg)
{
    thread_info *ti = (thread_info *)arg;
    while (ti->flag == 0)
    {
        printf("%c", ti->sym);
        fflush(stdout);
        sleep(1);
    }
    int *result = calloc(1, sizeof(int));
    *result = 2;
    return (void *)result;
}

int main()
{
    thread_info ti1;
    thread_info ti2;

    ti1.flag = 0;
    ti1.sym = '1';
    ti2.flag = 0;
    ti2.sym = '2';

    pthread_create(&ti1.id, NULL, proc1, &ti1);
    pthread_create(&ti2.id, NULL, proc2, &ti2);
    getchar();
    ti1.flag = 1;
    ti2.flag = 1;
    int *result1, *result2;
    pthread_join(ti1.id, (void **)&result1);
    pthread_join(ti2.id, (void **)&result2);
    printf("Result1: %d\n", *result1);
    printf("Result2: %d\n", *result2);
}