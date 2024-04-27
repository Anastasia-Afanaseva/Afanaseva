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
    int ret,val;
    int fd_fifo, y = 0;
    char buffer[20] = {};

    if ((sema_n = sem_open(SEM_NAME, 0600)) == SEM_FAILED)
    {
        perror("sem_open");
        return -1;
    }

    if((mkfifo("/home/nastya/myfifo.1", 0777)) == -1)
    {
        fprintf(stderr, "Невозможно создать fifo\n");
        exit(0);
    }

    fd_fifo = open("/home/nastya/myfifo.1", O_RDWR | O_CREAT | O_NONBLOCK, 0777);

    if (fd_fifo == -1) 
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++)
    {
        y += sprintf(buffer + y, "%d ", rand()%100);
    }

    if ((write(fd_fifo,buffer,strlen(buffer))) == -1)
    {
        printf("\nОшибка записи в файл");
        exit(0);
    }

    if (sem_post(sema_n) != 0)
    {
        perror("post error");
    }

    printf("\n%s", buffer);
    return 0;
}