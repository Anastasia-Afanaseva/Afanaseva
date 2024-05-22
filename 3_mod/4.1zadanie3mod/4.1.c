#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun
{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo *__buf;
};

int main()
{
    key_t key = 1;
    int fd_fifo, y = 0, semid;
    char buffer[20] = {};
    union semun arg;
    struct sembuf sm1 = {0, -1, SEM_UNDO};
    struct sembuf sm2 = {0, +1, SEM_UNDO};

    unlink("/home/nastya/myfifo.1");
    semid = semget(key, 1, 0666);

    if (semid < 0)
    {
        printf("Ошибка создания семафора\n");
        return 1;
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

    if ((semop(semid, &sm2, 1)) < 0)
    {
        printf("Ошибка\n");
        return 1;
    }

    printf("\n%s", buffer);
    return 0;
}