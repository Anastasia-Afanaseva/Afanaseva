#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "funk.h"
#define SEM_NAME "/mysem"
#define SHM_NAME_1 "/myshm"
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>

int cnt = 0;
int main()
{
    sem_t *sema_n;
    num_t *data;
    pid_t pid;
    int j = 0, rv, shar_mem;
    atexit(func_end);
    int num_1, num_2;

    //создание семафора
    if ((sema_n = sem_open(SEM_NAME, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        perror("sem_open");
        return -1;
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
        num_1 = (1 + rand()%10);
        num_2 = (1 + rand()%10);
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
                sem_wait(sema_n);
                data = mmap(NULL, 1000*sizeof(num_t), PROT_READ|PROT_WRITE, MAP_SHARED, shar_mem, 0);
                //поиск максимума и минимума
                min_max(data, num_1,num_2);
                munmap(NULL, 1000*sizeof(num_t));
                exit(EXIT_SUCCESS);
            }
            default:
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

                data = mmap(NULL, 1000*sizeof(num_t), PROT_READ|PROT_WRITE, MAP_SHARED, shar_mem, 0);
                //вывод максимумов и минимумов
                for (int i = 0; i < num_1; i++)
                {
                    printf("\n%d  %d", data->max_min[0], data->max_min[1]);
                    data = data + sizeof(num_t);
                }

                munmap(NULL, 1000*sizeof(num_t));
            }
        }
        cnt++;
        signal(SIGINT,&handler);
    }
    exit(0);
}