#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

int personid[10] = {0};
key_t key = 20;
struct msgbuf 
{
    long mtype;
    char mtext[50];
};

int main()
{
    int opt,cnt = 0,cnt_1, id = 0;
    char str[7];
    char string[40];
    int msqid, y = 0, i = 0;
    struct msgbuf msg_send, msg_rec;

    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0)
    {
        perror("msgget error");
        exit(1);
    }

    while (1)
    {
        printf("\nВыберите необходимую функцию:"
                "\n1 - Авторизовать клиента"
                "\n2 - Получить и разослать сообщение"
                "\n3 - Вывести список участников чата"
                "\n4 - Выключить чат\n");
        scanf("%d", &opt);

        switch(opt)
        {
            case 1:
            {
                memset(msg_rec.mtext, 0, strlen(msg_rec.mtext));
                msg_rec.mtype = 1;

                //получение сообщения с приоритетом равным 1
                if (msgrcv(msqid, &msg_rec, sizeof(msg_rec.mtext), msg_rec.mtype, MSG_NOERROR| IPC_NOWAIT) == -1)
                {
                    if (errno != ENOMSG)
                    {
                        perror("msgrcv");
                    }

                    printf("\nНет клиентов, доступных для авторизации\n");
                    break;
                }
                else
                {
                    //проверка, есть ли еще клиенты с таким id
                    cnt = 0;
                    cnt_1 = 0;
                    while (personid[cnt_1] != 0)
                    {
                        if (personid[cnt_1] == atoi(msg_rec.mtext))
                        {
                            cnt = 1;
                            id = personid[cnt_1];
                        }
                        cnt_1++;
                    }

                    //если id повторяется, то отправляем клиенту сообщение, что он не добавлен в чат
                    if (cnt == 1)
                    {
                        msg_send.mtype = id;
                        printf("\nТакой пользователь уже есть в чате");
                        snprintf(msg_send.mtext, sizeof(msg_send.mtext), "%s", "Вы не авторизованы");

                        if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), IPC_NOWAIT) == -1)
                        {
                            perror("msgsnd error");
                            exit(0);
                        }

                        snprintf(msg_send.mtext, sizeof(msg_send.mtext), "%s", "Такой id уже есть");
                        if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), IPC_NOWAIT) == -1)
                        {
                            perror("msgsnd error");
                            exit(0);
                        }

                        break;
                    }

                    //если клиент добавлен
                    personid[i] = atoi(msg_rec.mtext);
                    printf("\nПользователь %d добавлен в чат", personid[i]);
                    i++;
                }
                break;
            }
            case 2:
            {
                cnt_1 = 0;
                msg_rec.mtype = 2;

                //читаем сообщения в очереди с приоритетом 2
                //в первом сообщении id клиента, во втором само сообщение
                if (msgrcv(msqid, &msg_rec, sizeof(msg_rec.mtext), msg_rec.mtype, MSG_NOERROR| IPC_NOWAIT) == -1)
                {
                    if (errno != ENOMSG)
                    {
                        perror("msgrcv");
                    }

                    printf("\nНет сообщений, доступных для получения\n");
                    break;
                }

                id = atoi(msg_rec.mtext);

                memset(msg_rec.mtext,0,sizeof(msg_rec.mtext));
                if (msgrcv(msqid, &msg_rec, sizeof(msg_rec.mtext), msg_rec.mtype, MSG_NOERROR| IPC_NOWAIT) == -1)
                {
                    if (errno != ENOMSG)
                    {
                        perror("msgrcv");
                    }

                    printf("\nНет сообщений, доступных для получения\n");
                    break;
                }

                //отправляем всем клиентам сообщение id клиента и его сообщение
                while (personid[cnt_1] != 0)
                {
                    y = 0;
                    memset(str, 0, sizeof(str));
                    y += sprintf(str + y, "%d", id);
                    snprintf(msg_send.mtext, sizeof(msg_send.mtext), "%s", str);
                    msg_send.mtype = personid[cnt_1];

                    if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), IPC_NOWAIT) == -1)
                    {
                        perror("msgsnd error");
                        exit(0);
                    }

                    memset(msg_send.mtext, 0, sizeof(msg_send.mtext));
                    snprintf(msg_send.mtext, sizeof(msg_send.mtext), "%s", msg_rec.mtext);

                    if (msgsnd(msqid, &msg_send, sizeof(msg_send.mtext), IPC_NOWAIT) == -1)
                    {
                        perror("msgsnd error");
                        exit(0);
                    }
                    cnt_1++;
                }

                printf("\nСообщения отправлены всем пользователям чата");
                break;
            }
            case 3:
            {
                //вывод всех пользователей чата
                cnt_1 = 0;
                if (personid[0] != 0)
                {
                    while (personid[cnt_1] != 0)
                    {
                        printf("\nУчастник %d: %d", cnt_1 + 1,personid[cnt_1]);
                        cnt_1++;
                    }
                    break;
                }
                else
                {
                    printf("\nНет участников чата");
                    break;
                }
            }
            case 4:
            {
                //завершение чата
                printf("\nЧат завершен");
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