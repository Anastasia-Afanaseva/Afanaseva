#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "func.h"

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

void func_end(void)
{
    printf("\nУспешное завершение работы программы\n");
}