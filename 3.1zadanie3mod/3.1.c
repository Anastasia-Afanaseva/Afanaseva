#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct msgbuf 
{
    long mtype;
    char mtext[20];
};

int main()
{
    char str[10];
    int msqid, y = 0, key = 136;
    struct msgbuf msg;
    msg.mtype = 1;

    if ((msqid = msgget(key, IPC_CREAT | 0666 | IPC_EXCL)) < 0)
    {
        perror("msgget error");
        exit(1);
    }

    for (int i = 0; i < rand()%10; i++)
    {
        y = 0;
        memset(str, 0, sizeof(str));
        y += sprintf(str + y, "%d", rand()%100);
        snprintf(msg.mtext, sizeof(msg.mtext), "%s", str);

        if (msgsnd(msqid, &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1)
        {
            perror("msgsnd error");
            exit(EXIT_FAILURE);
        }
    }

    y = 0;
    memset(str, 0, sizeof(str));
    y += sprintf(str + y, "%d", 255);
    snprintf(msg.mtext, sizeof(msg.mtext), "%s", str);

    if (msgsnd(msqid, &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1)
    {
        perror("msgsnd error");
        exit(EXIT_FAILURE);
    }

    exit(0);
}