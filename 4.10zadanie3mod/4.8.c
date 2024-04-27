#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "funk.h"
#define SEM_NAME "/mysem"
#define SEM_NAME_2 "/mysem_1"
#define SEM_NAME_3 "/mysem_2"
#define SHM_NAME_1 "/myshm"
#include <semaphore.h>
#include <sys/mman.h>

int cnt = 0;
int main()
{
    sem_t *sema_n, *sema_n_1, *sema_n_2;
    num_t *data;
    pid_t pid, pid_1, pid_2;
    int j = 0,rv,shar_mem;
    int num_1, num_2;
    atexit(func_end);

    //создание семафора для 1 дочернего процесса
    if ((sema_n = sem_open(SEM_NAME, O_CREAT, 0666, 0)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(0);
    }
    //создание семафора для 2 дочернего процесса
    if ((sema_n_1 = sem_open(SEM_NAME_2, O_CREAT, 0666, 0)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(0);
    }
    //создание семафора для 3 дочернего процесса
    if ((sema_n_2 = sem_open(SEM_NAME_3, O_CREAT|O_TRUNC, 0666, 0)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(0);
    }

    //создание сегмента разделенной памяти
    if ((shar_mem = shm_open(SHM_NAME_1, O_CREAT|O_RDWR|O_TRUNC, 0666)) == -1)
    {
        printf("\nОшибка создания сегмента разделенной памяти");
        exit(0);
    }

    ftruncate(shar_mem, 1000*sizeof(num_t));

    while(1)
    {
        num_1 = 1 + rand()%10;
        num_2 = 1 + rand()%10;

        //первый дочерний процесс
        if((pid = fork()) == 0)
        {
            //блокируем доступ
            sem_wait(sema_n);
            data = mmap(NULL, 1000*sizeof(num_t), PROT_READ|PROT_WRITE, MAP_SHARED, shar_mem, 0);
            //поиск максимума и минимума
            min_max(data, num_1,num_2);
            munmap(NULL, 1000*sizeof(num_t));

            if (sem_post(sema_n_1) != 0)
            {
                perror("post error");
            }

            exit(EXIT_SUCCESS);
        }

        //второй дочерний процесс
        if ((pid > 0) && ((pid_1 = fork()) == 0))
        {
            //блокируем доступ
            sem_wait(sema_n_1);
            data = mmap(NULL, 1000*sizeof(num_t), PROT_READ|PROT_WRITE, MAP_SHARED, shar_mem, 0);
            //поиск суммы
            summar(data, num_1,num_2);
            munmap(NULL, 1000*sizeof(num_t));

            if (sem_post(sema_n_2) != 0)
            {
                perror("post error");
            }

            exit(EXIT_SUCCESS);
        }

        //третий дочерний процесс
        if ((pid > 0) && (pid_1 > 0) && ((pid_2 = fork()) == 0))
        {
            //блокируем доступ
            sem_wait(sema_n_2);
            data = mmap(NULL, 1000*sizeof(num_t), PROT_READ|PROT_WRITE, MAP_SHARED, shar_mem, 0);
            //поиск среднего значения
            middle_num(data, num_1,num_2);
            munmap(NULL, 1000*sizeof(num_t));
            exit(EXIT_SUCCESS);
        }

        //ошибка fork
        if ((pid_1 < 0) || (pid_1 < 0) || (pid < 0))
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if ((pid_1 > 0) || (pid_1 > 0) || (pid > 0))
        {
            data = mmap(NULL, 1000*sizeof(num_t), PROT_READ | PROT_WRITE, MAP_SHARED, shar_mem, 0);
            //помещаем рандомные значения
            print_num(data,num_1,num_2);
            munmap(NULL, 1000*sizeof(num_t));

            //разблокируем доступ
            if (sem_post(sema_n) != 0)
            {
                perror("post error");
            }

            wait(&rv);
            wait(&rv);
            wait(&rv);
            data = mmap(NULL, 1000*sizeof(num_t), PROT_READ | PROT_WRITE, MAP_SHARED, shar_mem, 0);

            //вывод максимумов и минимумов
            for (int i = 0; i < num_1; i++)
            {
                printf("\nMIDDLE_NUM = %d", data->middle);
                printf("\nMAX = %d  MIN = %d", data->max_min[0], data->max_min[1]);
                printf("\nSUMM = %d", data->summ);
                data = data + sizeof(num_t);
            }

            munmap(NULL, 1000*sizeof(num_t));
        }

        cnt++;
        signal(SIGINT,&handler);
    }
    exit(0);
}