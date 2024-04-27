#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include "funk.h"

int main(int argc, char *argv[])
{
    union semun arg;
    atexit(func);
    int num, j = 0, rv, fd, semid;
    char str[80] = {0};
    char string[80] = {0};
    int p[2];
    pid_t pid;
    key_t key = 1;
    struct sembuf lock_res = {0, -1, SEM_UNDO};
    struct sembuf rel_res = {0, +1, SEM_UNDO};
    struct sembuf P[1] = {{1, -1, 0}};
    struct sembuf V[1] = {{0, 1, IPC_NOWAIT}};

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

    if ((fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0600)) == -1)
    {
        printf("\n\tНе удалось открыть файл");
        return 0;
    }

    if (close(fd) == -1)
    {
        fprintf(stderr,"\n\tПроизошла ошибка закрытия файла");
        return 0;
    }

    if ((semid = semget(key, 2, 0666 | IPC_CREAT)) < 0)
    {
        printf("Ошибка семафора\n");
        return 1;
    }

    arg.val = 0;

    //семафор на контроль одновременной записи и чтения
    if ((semctl(semid, 0, SETVAL, arg)) < 0)
    {
        printf("Ошибка\n");
        return 1;
    }

    arg.val = 2;

    //семафор на одновременное чтение несколькими процессами
    if ((semctl(semid, 1, SETVAL, arg)) < 0)
    {
        printf("Ошибка\n");
        return 1;
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

            //уменьшаем оба семофоры на 1, 0 - блокирует чтение, пока запись
            if ((semop(semid, &lock_res, 1)) < 0)
            {
                perror("Ошибка\n");
                return 1;
            }

            //уменьшаем семафор чтения, теперь читать одновременно может 1 процесс
            if ((semop(semid, P, 1)) < 0)
            {
                perror("Ошибка\n");
                return 1;
            }

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

            //увеличиваем семафор чтения, теперь читать одновременно может 2 процесса
            if ((semop(semid, V, 1)) < 0)
            {
                perror("Ошибка\n");
                return 1;
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

            //разблокируем семафор контроля записи-чтения
            if ((semop(semid, &rel_res, 1)) < 0)
            {
                perror("Ошибка\n");
                return 1;
            }

            wait(&rv);
            read(p[0], &string, sizeof(string));
            printf("\nСообщение от дочернего процесса 2: %s", string);
            close(p[0]);
            semctl(semid, 0, IPC_RMID);
        }
    }
}