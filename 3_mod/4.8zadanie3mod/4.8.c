#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "funk.h"

int cnt = 0;
int main()
{
    num_t *data;
    union semun arg;
    pid_t pid, pid_1, pid_2;
    int j = 0, rv, semid,shar_mem;
    struct sembuf sm1 = {0, -1, SEM_UNDO};
    struct sembuf sm2 = {0, +1, SEM_UNDO};
    struct sembuf P[1] = {{1, -1, 0}};
    struct sembuf V[1] = {{1, 1, IPC_NOWAIT}};
    struct sembuf P2[1] = {{2, -1, 0}};
    struct sembuf V2[1] = {{2, 1, IPC_NOWAIT}};
    atexit(func_end);

    //создание семафора
    if ((semid = semget(IPC_PRIVATE, 3, 0666 | IPC_CREAT)) < 0)
    {
        printf("Ошибка семафора\n");
        return 1;
    }

    //создание сегмента разделенной памяти
    if ((shar_mem = shmget(IPC_PRIVATE, 1000*sizeof(num_t), O_CREAT | 0666)) == -1)
    {
        printf("\nОшибка создания сегмента разделенной памяти");
        exit(0);
    }

    arg.val = 0;

    if ((semctl(semid, 0, SETVAL, arg)) < 0)
    {
        printf("Ошибка\n");
        return 1;
    }

    if ((semctl(semid, 1, SETVAL, arg)) < 0)
    {
        printf("Ошибка\n");
        return 1;
    }

    if ((semctl(semid, 2, SETVAL, arg)) < 0)
    {
        printf("Ошибка\n");
        return 1;
    }

    while(1)
    {
        int num_1 = 1 + rand()%10;
        int num_2 = 1 + rand()%10;

        //первый дочерний процесс
        if((pid = fork()) == 0) 
        {
            //блокируем доступ
            if ((semop(semid, &sm1, 1)) < 0)
            {
                printf("Ошибка 1\n");
                return 1;
            }

            data = shmat(shar_mem, 0, 0);
            //поиск максимума и минимума
            min_max(data, num_1,num_2);
            shmdt(data);
            //разблокируем доступ для второго дочернего процесса
            if ((semop(semid, V, 1)) < 0)
            {
                printf("Ошибка 2\n");
                return 1;
            }

            exit(EXIT_SUCCESS);
        }

        //второй дочерний процесс
        if ((pid > 0) && ((pid_1 = fork()) == 0))
        {
            //блокируем доступ
            if ((semop(semid, P, 1)) < 0)
            {
                printf("Ошибка 2\n");
                return 1;
            }

            data = shmat(shar_mem, 0, 0);
            //поиск суммы
            summar(data, num_1,num_2);
            shmdt(data);
            //разблокируем доступ для третьего дочернего процесса
            if ((semop(semid, V2, 1)) < 0)
            {
                printf("Ошибка 3\n");
                return 1;
            }

            exit(EXIT_SUCCESS);
        }

        //третий дочерний процесс
        if ((pid > 0) && (pid_1 > 0) && ((pid_2 = fork()) == 0))
        {
            //блокируем доступ
            if ((semop(semid, P2, 1)) < 0)
            {
                printf("Ошибка 3\n");
                return 1;
            }

            data = shmat(shar_mem, 0, 0);
            //поиск среднего значения
            middle_num(data, num_1,num_2);
            shmdt(data);
            exit(EXIT_SUCCESS);
        }
        //ошибка fork
        if ((pid_1 < 0) || (pid_1 < 0) || (pid < 0))
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if ((pid_1 > 0) && (pid_1 > 0) && (pid > 0))
        {
            data = shmat(shar_mem, 0, 0);
            //помещаем рандомные значения
            print_num(data,num_1,num_2);
            shmdt(data);

            //разблокируем доступ
            if ((semop(semid, &sm2, 1)) < 0)
            {
                printf("Ошибка\n");
                return 1;
            }

            wait(&rv);
            wait(&rv);
            wait(&rv);
            data = shmat(shar_mem, 0, 0);
            //вывод максимумов и минимумов
            for (int i = 0; i < num_1; i++)
            {
                printf("\nMIDDLE_NUM = %d", data->middle);
                printf("\nMAX = %d  MIN = %d", data->max_min[0], data->max_min[1]);
                printf("\nSUMM = %d", data->summ);
                data = data + sizeof(num_t);
            }

            shmdt(data);
        }
        cnt++;
        signal(SIGINT,&handler);
    }

    exit(0);
}