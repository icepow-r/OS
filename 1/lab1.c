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
    pthread_exit((void *)1); /* завершение потока с возвратом кода завершения 1 */
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
    pthread_exit((void *)2); /* завершение потока с возвратом кода завершения 2 */
}

int main()
{
    printf("программа начала работу");
    thread_info ti1;
    thread_info ti2;

    ti1.flag = 0;
    ti1.sym = '1';
    ti2.flag = 0;
    ti2.sym = '2';

    pthread_create(&ti1.id, NULL, proc1, &ti1); /* создание потока 1: ti1.id - дескриптор потока, NULL - атрибуты по умолчанию, proc1 - поточная функция, &ti1 - передаваемый параметр */
    printf("поток 1 начал работу\n");

    pthread_create(&ti2.id, NULL, proc2, &ti2); /* создание потока 2: ti2.id - дескриптор потока, NULL - атрибуты по умолчанию, proc2 - поточная функция, &ti2 - передаваемый параметр */
    printf("поток 2 начал работу\n");

    printf("программа ждет нажатия клавиши\n");
    getchar();
    printf("клавиша нажата\n");

    ti1.flag = 1;
    ti2.flag = 1;

    int *result1, *result2;

    pthread_join(ti1.id, (void **)&result1); /* ожидание завершения потока 1: ti1.id - дескриптор потока, result1 - указатель для получения кода завершения потока */
    printf("поток 1 закончил работу\n");

    pthread_join(ti2.id, (void **)&result2); /* ожидание завершения потока 2: ti2.id - дескриптор потока, result2 - указатель для получения кода завершения потока */
    printf("поток 2 закончил работу\n");

    printf("код завершения 1 потока: %p\n", result1);
    printf("код завершения 2 потока: %p\n", result2);
    printf("программа завершила работу\n");
}