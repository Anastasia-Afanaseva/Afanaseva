#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

key_t key = 20;
struct msgbuf 
{
    long mtype;
    char mtext[50];
};

int main()
{
    int opt,cnt = 0,opt_1;
    char str[10];
    int msqid, y = 0;
    struct msgbuf msg_send, msg_rec;
    int type;

    while (1)
    {
        printf("\nВыберите необходимую функцию:"
                "\n1 - Вступить в чат"
                "\n2 - Отправить сообщение"
                "\n3 - Прочитать сообщение"
                "\n4 - Выход\n");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
            {
                if (cnt != 0)
                {
                    printf("\nВы уже регистрировались в чате");
                    break;
                }

                if ((msqid = msgget(key, 0666)) < 0)
                {
                    if(errno == ENOENT)
                    {
                        printf("\nЧат еще не создан");
                        break;
                    }
                    perror("msgget error");
                    exit(1);
                }

                printf("\nВведите идентификатор:");
                scanf("%d", &opt_1);
                type = opt_1;
                msg_send.mtype = 1;
                y = 0;
                memset(str, 0, sizeof(str));
                y += sprintf(str + y, "%d", type);
                snprintf(msg_send.mtext, sizeof(msg_send.mtext), "%s", str);
                printf("\nОтправляю идентификатор %s",msg_send.mtext);


                //отправление сообщения с приоритетом 1, в сообщении которого идентификатор клиента
                if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), IPC_NOWAIT) == -1)
                {
                    if (errno == EINVAL)
                    {
                        printf("\nЧат завершен");
                        exit(0);
                    }

                    perror("msgsnd error");
                }
                cnt = 1;

                break;
            }
            case 2:
            {
                if (cnt != 1)
                {
                    printf("\nВы еще не зарегистрировались в чате");
                    break;
                }

                //отправление два сообщения с приоритетом 2, первое - id, второе - сообщение
                msg_send.mtype = 2;
                y = 0;
                memset(str, 0, sizeof(str));
                y += sprintf(str + y, "%d", type);
                snprintf(msg_send.mtext, sizeof(msg_send.mtext), "%s", str);

                if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), IPC_NOWAIT) == -1)
                {
                    if (errno == EINVAL)
                    {
                        printf("\nЧат завершен");
                        exit(0);
                    }

                    perror("msgsnd error");
                }

                printf("\nВведите сообщение для отправки в чат\n");
                memset(str, 0, sizeof(str));
                getchar();
                fgets(str, sizeof(str),stdin);
                snprintf(msg_send.mtext, sizeof(msg_send.mtext), "%s", str);

                if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), IPC_NOWAIT) == -1)
                {
                    if (errno == EINVAL)
                    {
                        printf("\nЧат завершен");
                        exit(0);
                    }

                    perror("msgsnd error");
                }

                printf("\nСообщение отправлено");
                break;
            }
            case 3:
            {
                if (cnt != 1)
                {
                    printf("\nВы еще не зарегистрировались в чате");
                    break;
                }

                //получение сообщения с приоритетом, равным id клиента
                msg_rec.mtype = type;
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
                    //в тексте сообщения id клиента, который посылает сообщение
                    printf("Пользователь: %s\n", msg_rec.mtext);
                }

                //получение сообщения от клиента чата
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
                    printf("Сообщение: %s\n", msg_rec.mtext);
                }

                break;
            }
            case 4:
            {
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