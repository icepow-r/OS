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
        printf("%c", ti->sym); /* вывод символа на стандартный вывод */
        fflush(stdout);        /* принудительная очистка буфера стандартного вывода для немедленного отображения символа */
        sleep(1);              /* приостановка выполнения потока на 1 секунду */
    }
    pthread_exit((void *)1); /* завершение потока с возвратом кода завершения 1 */
}

void *proc2(void *arg)
{
    thread_info *ti = (thread_info *)arg;
    while (ti->flag == 0)
    {
        printf("%c", ti->sym); /* вывод символа на стандартный вывод */
        fflush(stdout);        /* принудительная очистка буфера стандартного вывода для немедленного отображения символа */
        sleep(1);              /* приостановка выполнения потока на 1 секунду */
    }
    pthread_exit((void *)2); /* завершение потока с возвратом кода завершения 2 */
}

int main()
{
    thread_info ti1;
    thread_info ti2;

    ti1.flag = 0;
    ti1.sym = '1';
    ti2.flag = 0;
    ti2.sym = '2';

    pthread_create(&ti1.id, NULL, proc1, &ti1); /* создание потока 1: ti1.id - дескриптор потока, NULL - атрибуты по умолчанию, proc1 - поточная функция, &ti1 - передаваемый параметр */
    printf("Поток 1 создан\n");

    pthread_create(&ti2.id, NULL, proc2, &ti2); /* создание потока 2: ti2.id - дескриптор потока, NULL - атрибуты по умолчанию, proc2 - поточная функция, &ti2 - передаваемый параметр */
    printf("Поток 2 создан\n");

    printf("Ожидание нажатия клавиши\n");
    getchar(); /* чтение одного символа из стандартного ввода, блокирует выполнение до нажатия Enter */
    printf("Клавиша нажата\n");

    ti1.flag = 1;
    ti2.flag = 1;

    int *result1, *result2;

    pthread_join(ti1.id, (void **)&result1); /* ожидание завершения потока 1: ti1.id - дескриптор потока, result1 - указатель для получения кода завершения потока */
    printf("Поток 1 остановлен\n");

    pthread_join(ti2.id, (void **)&result2); /* ожидание завершения потока 2: ti2.id - дескриптор потока, result2 - указатель для получения кода завершения потока */
    printf("Поток 2 остановлен\n");

    printf("Код завершения 1 потока: %p\n", result1);
    printf("Код завершения 2 потока: %p\n", result2);
    printf("Программа завершила работу\n");
}