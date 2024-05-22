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
    int msqid, key = 136;
    struct msgbuf msg_1;

    if ((msqid = msgget(key, 0666)) < 0)
    {
        perror("msgget");
        exit(1);
    }

    while(atoi(msg_1.mtext) != 255)
    {
        if (msgrcv(msqid, &msg_1, sizeof(msg_1.mtext), msg_1.mtype, MSG_NOERROR | IPC_NOWAIT) == -1) 
        {
            if (errno != ENOMSG)
            {
                perror("msgrcv");
                exit(EXIT_FAILURE);
            }

            printf("Нет сообщений, доступных для msgrcv()\n");
        }
        else
        {
            printf("Полученное сообщение: %s\n", msg_1.mtext);
        }
    }

    exit(0);
}