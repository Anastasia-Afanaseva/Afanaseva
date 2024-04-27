#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#define SEM_NAME "/mysem"
#include "func.h"

int main(int argc, char *argv[])
{
    sem_t *sema_n;
    int ret,val;
    atexit(func_end);
    int num, j = 0, rv, fd;
    char str[80] = {0};
    char string[80] = {0};
    int p[2];
    pid_t pid;

    if (argc == 1)
    {
        printf("\nНет ни одного числа для передачи");
        return 0;
    }

    if (pipe(p))
    {
        perror("\nОшибка канала");
        exit(1);
    }

    if ((sema_n = sem_open(SEM_NAME, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        perror("sem_open");
        return -1;
    }

    switch(pid = fork()) 
    {
        case -1:
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            close(p[0]);
            num = atoi(argv[1]);
            if (num > 0)
            {
                for (int i = 0; i < num; i++)
                {
                    j += sprintf(str + j, "%d ", rand()%100);
                }
            }
            else
            {
                printf("\nКоличество чисел равно нулю");
                exit(EXIT_SUCCESS);
            }

            write(p[1],str, strlen(str));
            sem_wait(sema_n);
            
            if ((fd = open("file.txt", O_RDWR, 0600)) == -1)
            {
                fprintf(stderr, "\n\tНе удалось открыть файл");
                return 0;
            }

            if ((read(fd, string, sizeof(string))) == -1)
            {
                fprintf(stderr, "\n\tПроизошла ошибка чтения");
                return 0;
            }

            if (close(fd) == -1)
            {
                fprintf(stderr, "\n\tПроизошла ошибка закрытия файла");
                return 0;
            }
            
            printf("\nСтрока после изменений родителя: %s", string);
            memset(string, 0, strlen(string));
            j = 0;
            j += sprintf(string + j, "%d ", rand()%1000);
            write(p[1], string, strlen(string));
            close(p[1]);
            exit(EXIT_SUCCESS);
        }
        default:
        {
            num = atoi(argv[1]);
            close(p[1]);
            read(p[0], str, sizeof(str));
            fprintf(stderr, "\nСообщение от дочернего процесса: %s", str);
            change_parent(num, str);

            if (sem_post(sema_n) != 0)
            {
                perror("post error");
            }

            wait(&rv);
            read(p[0], &string, sizeof(string));
            printf("\nСообщение от дочернего процесса 2: %s", string);
            close(p[0]);
            sem_close(sema_n);
            sem_unlink(SEM_NAME);
        }
    }
}