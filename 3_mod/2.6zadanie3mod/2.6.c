#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

static int m = 0;

void handle(int val)
{
    if (m < 3)
    {
        signal(SIGINT,SIG_IGN);
        printf("\nSIGINT %d", m);
    }
    else
    {
        signal(SIGINT,SIG_DFL);
        printf("\nSIGINT");
        exit(0);
    }
    m++;
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

    while (1)
    {
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

        if (signal(SIGINT, &handle) == SIG_ERR)
        {
            printf("\nОшибка обработчика");
            return 0;
        }
        i++;    
        sleep(1);
    }
}