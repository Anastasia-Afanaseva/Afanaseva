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
    int semid, fd_fifo;
    char buf[50] = "";
    union semun arg;
    struct sembuf sm1 = {0, -1, SEM_UNDO};
    struct sembuf sm2 = {0, +1, SEM_UNDO};

    if ((semid = semget(key, 1, 0666 | IPC_CREAT)) < 0)
    {
        printf("Ошибка семафора\n");
        return 1;
    }

    arg.val = 0;

    if ((semctl(semid, 0, SETVAL, arg)) < 0)
    {
        printf("Ошибка\n");
        return 1;
    }

    if ((semop(semid, &sm1, 1)) < 0)
    {
        printf("Ошибка\n");
        return 1;
    }

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
    semctl(semid, 0, IPC_RMID);
    unlink("/home/nastya/myfifo.1");
    return 0;
}