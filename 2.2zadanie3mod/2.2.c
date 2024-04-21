#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void parent_process(char *str, char *str_1)
{
    int j = 0,i = 0, m = 0;
    char tmp[10] = {0};
    i = 0; j = 0;

    while (i != strlen(str))
    {
        if ((str[i] != ' ') && (str[i] != '\0'))
        {
            tmp[j] = str[i];
            j++;
        }
        else
        {
            m += sprintf(str_1 + m, "%d ", atoi(tmp) * 2);
            memset(tmp, 0, 10);
            j = 0;
        }
        i++;
    }
}

void write_file(char *str)
{
    int fd;
    if ((fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
    {
        printf("\n\tНе удалось открыть файл");
        getchar();
        return;
    }

    if (write(fd, str, strlen(str)) == -1)
    {
        printf("\n\tПроизошла ошибка записи");
        return;
    }

    if (close(fd) == -1)
    {
        printf("\n\tПроизошла ошибка закрытия файла");
        return;
    }
}

void func(void)
{
    printf("\nУспешное завершение работы программы\n");
}

int main(int argc, char *argv[])
{
    atexit(func);
    int fd, num, j = 0, rv;
    char str[80] = {0};
    char str_1[80] = {0};
    int p1[2], p2[2];
    pid_t pid;

    if (argc == 1)
    {
        printf("\nНет ни одного числа для передачи");
        return 0;
    }

    if (pipe(p1))
    {
        perror("\nОшибка канала p1");
        exit(1);
    }

    if (pipe(p2))
    {
        perror("\nОшибка канала p2");
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
            close(p1[0]);
            num = atoi(argv[1]);
            if (num > 0)
            {
                for (int i = 0; i < num; i++)
                {
                    j += sprintf(str + j, "%d ", rand()%1000);
                }
            }
            else
            {
                printf("\nКоличество чисел равно нулю");
                exit(EXIT_SUCCESS);
            }

            write(p1[1],str, strlen(str));
            close(p1[1]);
            close(p2[1]);
            read(p2[0], str_1, sizeof(str_1));
            printf("\nСообщение от родительского процесса: %s", str_1);
            close(p2[0]);
            exit(1);
        }
        default:
        {
            close(p1[1]);
            read(p1[0], str, sizeof(str));
            printf("\nСообщение от дочернего процесса: %s", str);
            write_file(str);
            parent_process(str, str_1);
            close(p1[0]);
            
            close(p2[0]);
            write(p2[1],str_1, strlen(str_1));
            close(p2[1]);
            wait(&rv);
        }
    }
}