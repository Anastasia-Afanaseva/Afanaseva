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
    pid_t pid;
    int j = 0, rv, semid,shar_mem;
    struct sembuf sm1 = {0, -1, SEM_UNDO};
    struct sembuf sm2 = {0, +1, SEM_UNDO};
    atexit(func_end);

    //создание семафора
    if ((semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) < 0)
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

    while(1)
    {
        int num_1 = 1 + rand()%10;
        int num_2 = 1 + rand()%10;
        switch(pid = fork()) 
        {
            case -1:
            {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            case 0:
            {
                //блокируем доступ
                if ((semop(semid, &sm1, 1)) < 0)
                {
                    printf("Ошибка\n");
                    return 1;
                }

                data = shmat(shar_mem, 0, 0);
                //поиск максимума и минимума
                min_max(data, num_1,num_2);
                shmdt(data);
                exit(EXIT_SUCCESS);
            }
            default:
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
                data = shmat(shar_mem, 0, 0);

                //вывод максимумов и минимумов
                for (int i = 0; i < num_1; i++)
                {
                    printf("\n%d  %d", data->max_min[0], data->max_min[1]);
                    data = data + sizeof(num_t);
                }

                shmdt(data);
            }
        }
        cnt++;
        signal(SIGINT,&handler);
    }
    exit(0);
}