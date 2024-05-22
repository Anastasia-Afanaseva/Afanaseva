#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

key_t key = 19;
struct msgbuf 
{
    long mtype;
    char mtext[30];
};

int main(int argc, char *argv[])
{
    int opt;
    char str[30];
    int msqid, y = 0;
    struct msgbuf msg_send, msg_rec;

    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0)
    {
        if (errno == EEXIST)
        {
            msqid = msgget(key, 0666);
        }
        else
        {
            perror("msgget error");
            exit(1);
        }
    }

    if ((argc == 1) || (atoi(argv[1]) <= 0))
    {
        printf("\nНекорректно указан приоритет");
        exit(0);
    }

    msg_send.mtype = atoi(argv[1]);

    if (atoi(argv[1]) == 100)
    {
        msg_rec.mtype = 200;
    }
    else
    {
        msg_rec.mtype = 100;
    }

    while (1)
    {
        printf("\nВыберите необходимую функцию:"
                "\n1 - Отправить сообщение"
                "\n2 - Прочитать сообщение"
                "\n3 - Покинуть чат\n");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
            {
                //отправка сообщений
                printf("\nВведите сообщение для отправки: ");
                memset(str, 0, sizeof(str));
                getchar();
                fgets(str, sizeof(str),stdin);
                snprintf(msg_send.mtext, sizeof(msg_send.mtext), "%s", str);

                if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), IPC_NOWAIT) == -1)
                {
                    if (errno == EINVAL)
                    {
                        printf("\nСобеседник покинул чат");
                        exit(0);
                    }

                    perror("msgsnd error");
                }

                printf("\nСообщение отправлено");
                break;
            }
            case 2:
            {
                //получение сообщения
                memset(msg_rec.mtext, 0, strlen(msg_rec.mtext));

                if (msgrcv(msqid, &msg_rec, sizeof(msg_rec.mtext), msg_rec.mtype, MSG_NOERROR| IPC_NOWAIT) == -1)
                {
                    if (errno == EINVAL)
                    {
                        printf("\nСобеседник покинул чат");
                        exit(0);
                    }

                    if (errno != ENOMSG)
                    {
                        perror("msgrcv");
                    }

                    printf("\nНет сообщений, доступных для получения\n");
                    break;
                }
                else
                {
                    printf("Полученное сообщение: %s\n", msg_rec.mtext);
                }
                

                break;
            }
            case 3:
            {
                msgctl(msqid, IPC_RMID, NULL);
                exit(0);
            }
            default:
            {
                printf("\nВведено некорректное значение");
                break;
            }
        }
    }
}