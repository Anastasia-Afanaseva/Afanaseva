#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    int fd, j, i = 1, num;
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
        i++;
        sleep(1);
    }
    close(fd);
    return 0;
}