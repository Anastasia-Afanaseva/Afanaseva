#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void func(void)
{
    printf("\nУспешное завершение работы программы\n");
}
int main(int argc, char *argv[])
{
    atexit(func);
    int fd, num, j = 0, rv;
    char str[80] = {0};
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
                    j += sprintf(str + j, "%d ", rand()%1000);
                }
            }
            else
            {
                printf("\nКоличество чисел равно нулю");
                exit(EXIT_SUCCESS);
            }

            write(p[1],str, strlen(str));
            close(p[1]);
            exit(EXIT_SUCCESS);
        }
        default:
        {
            close(p[1]);
            wait(&rv);
            read(p[0], str, sizeof(str));
            printf("\nСообщение от дочернего процесса: %s", str);
            if ((fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
            {
                printf("\n\tНе удалось открыть файл");
                getchar();
                return 0;
            }

            if (write(fd, str, strlen(str)) == -1)
            {
                printf("\n\tПроизошла ошибка записи");
                return 0;
            }

            if (close(fd) == -1)
            {
                printf("\n\tПроизошла ошибка закрытия файла");
                return 0;
            }

            close(p[0]);
        }
    }
}