#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

int flag = 0;

void my_handler(int signum)
{
    fprintf(stderr, "\nReceived SIGUSR1!");
    sleep(1);
    return;
}

void my_handler_1(int signum)
{
    fprintf(stderr, "\nReceived SIGUSR2!");
    return;
}

void change_parent(int num, char *str)
{
    int fd;
    if ((fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
    {
        printf("\n\tНе удалось открыть файл");
        return;
    }

    int j = strlen(str);

    for (int i = 0; i < num; i++)
    {
        j += sprintf(str + j, "%d ", rand()%10);
    }

    if (write(fd, str, strlen(str)) == -1)
    {
        fprintf(stderr,"\n\tПроизошла ошибка записи");
        return;
    }

    if (close(fd) == -1)
    {
        fprintf(stderr,"\n\tПроизошла ошибка закрытия файла");
        return;
    }
    return;
}

void read_child(char *string)
{
    int fd;

    return;
}

void func(void)
{
    printf("\nУспешное завершение работы программы\n");
}

int main(int argc, char *argv[])
{
    int fd;
    atexit(func);
    int num, j = 0, rv;
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
            signal(SIGUSR1, my_handler);
            signal(SIGUSR2, my_handler_1);
            sleep(1);
            
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
            kill(pid, SIGUSR1);
            change_parent(num, str);
            kill(pid, SIGUSR2);
            wait(&rv);
            read(p[0], &string, sizeof(string));
            printf("\nСообщение от дочернего процесса 2: %s", string);
            close(p[0]);
        }
    }
}