#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

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
    pthread_exit((void *)1);
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
    pthread_exit((void *)2);
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
    printf("Поток 1 создан\n");
    pthread_create(&ti2.id, NULL, proc2, &ti2);
    printf("Поток 2 создан\n");

    printf("Ожидание нажатия клавиши\n");
    getchar();
    printf("Клавиша нажата\n");

    ti1.flag = 1;
    ti2.flag = 1;
    int *result1, *result2;

    pthread_join(ti1.id, (void **)&result1);
    printf("Поток 1 остановлен\n");

    pthread_join(ti2.id, (void **)&result2);
    printf("Поток 2 остановлен\n");

    printf("Код завершения 1 потока: %p\n", result1);
    printf("Код завершения 2 потока: %p\n", result2);
    printf("Программа завершила работу\n");
}