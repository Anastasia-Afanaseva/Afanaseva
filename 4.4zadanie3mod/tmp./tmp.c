#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#define SEM_NAME "/mysem"

int main()
{
    sem_t *sema_n;
    int ret,val, fd_fifo;
    char buf[50] = "";

    if ((sema_n = sem_open(SEM_NAME, O_CREAT, 0600, 0)) == SEM_FAILED)
    {
        perror("sem_open");
        return -1;
    }

    sem_wait(sema_n);

    fd_fifo = open("/home/nastya/myfifo.1", O_RDONLY | O_NONBLOCK , 0777);

    if (fd_fifo == -1) 
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if ((read(fd_fifo, buf, sizeof(buf))) == -1)
    {
        printf("\nОшибка чтения");
        exit(0);
    }

    printf("Строка вывода: %s", buf);
    close(fd_fifo);

    sem_close(sema_n);
    sem_unlink(SEM_NAME);
    unlink("/home/nastya/myfifo.1");
    return 0;
}