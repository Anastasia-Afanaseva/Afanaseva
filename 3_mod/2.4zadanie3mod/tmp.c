#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd_fifo;
    char buf[50] = "";

    fd_fifo = open("/home/nastya/myfifo.1", O_RDONLY | O_NONBLOCK , 0777);
    if (fd_fifo == -1) 
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    sleep(5);
    if ((read(fd_fifo, buf, sizeof(buf))) == -1)
    {
        printf("\nОшибка чтения");
        exit(0);
    }

    printf("\nСтрока вывода: %s", buf);
    close(fd_fifo);
return 0;
}