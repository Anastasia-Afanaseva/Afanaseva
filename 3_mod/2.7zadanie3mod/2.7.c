#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

void handler(int val)
{
    if (val == 3)
    {
        fprintf(stderr, "\nПолучен сигнал SIGQUIT");
        exit(0);
    }
    if (val == 2)
    {
        fprintf(stderr, "\nПолучен сигнал SIGINT");
        exit(0);
    }
}

int main()
{       
    int fd, j = 0, i = 1, num;
    char str[100];

    if ((fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
        {
            printf("\nОшибка при открытии файла");
            return 0;
        }
        close(fd);
    
    if (signal(SIGINT, &handler) == SIG_ERR)
    {
        printf("\nНе сработал обработчик SIGINT");
        exit(0);
    }
    if (signal(SIGQUIT, &handler) == SIG_ERR)
    {
        printf("\nНе сработал обработчик SIGQUIT");
        exit(0);
    }

    while (1)
    {
        if ((fd = open("file.txt", O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
        {
            printf("\nОшибка при открытии файла");
            return 0;
        }

        if ((num = read(fd, &str, strlen(str))) == -1)
        {
            printf("\nОшибка при чтении файла");
            return 0;
        }

        j += sprintf(str + j, "%d ", i);
        lseek(fd, num, SEEK_SET);
        if (write(fd, str, strlen(str)) == -1)
        {
            printf("\nОшибка при записи в файл");
            return 0;
        }

        close(fd);
        i++;
        sleep(1);
    }

    return 0;
}