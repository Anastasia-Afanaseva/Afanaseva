#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#define QUEUE_NAME "/my_queue"
#define SIZE 50

int personid[10] = {0};

int main()
{
    struct mq_attr queue_attr;
    queue_attr.mq_maxmsg = 10;
    queue_attr.mq_msgsize = SIZE;
    mqd_t ds;
    char str[SIZE], new_text[SIZE];
    int opt,cnt = 0,cnt_1, id = 0, i = 0, prio_recv, prio_send;

    if(mq_unlink(QUEUE_NAME) == 0)
    {
        fprintf(stdout, "Message queue %s removed from system.\n", QUEUE_NAME);
    }

    if ((ds = mq_open(QUEUE_NAME, O_RDWR | O_NONBLOCK | O_CREAT, 0666, &queue_attr)) == (mqd_t)-1)
    {
        perror("Creating queue error");
        return -1;
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
                //получение сообщения
                if (mq_receive(ds, new_text, SIZE, &prio_recv) == -1)
                {
                    printf("\nНет сообщений, доступных для получения\n");
                    perror("cannot receive");
                    break;
                }

                //проверка равен ли приоритет 1(для авторизации)
                if (prio_recv == 1)
                {
                    //проверка, есть ли еще клиенты с таким id
                    cnt = 0;
                    cnt_1 = 0;
                    while (personid[cnt_1] != 0)
                    {
                        if (personid[cnt_1] == atoi(new_text))
                        {
                            cnt = 1;
                            id = personid[cnt_1];
                        }
                        cnt_1++;
                    }

                    //если id повторяется, то отправляем клиенту сообщение, что он не добавлен в чат
                    if (cnt == 1)
                    {
                        printf("\nТакой пользователь уже есть в чате");

                        if (mq_send(ds, "Вы не авторизованы", strlen("Вы не авторизованы")+1, id) == -1)
                        {
                            perror("Sending message error");
                            break;
                        }

                        break;
                    }

                    //если клиент добавлен, отправляем соответствующее сообщение
                    personid[i] = atoi(new_text);
                    printf("\nПользователь %d добавлен в чат", personid[i]);
                    if (mq_send(ds, "Вы авторизованы", strlen("Вы авторизованы")+1, personid[i]) == -1)
                    {
                        perror("Sending message error");
                        break;
                    }
                    i++;
                }
                else
                {
                    //если приоритет не равен 1 сообщение отправляется обратно в очередь
                    printf("\nПрочитано сообщение для клиента");

                    if (mq_send(ds, new_text, strlen(new_text)+1, prio_recv) == -1)
                    {
                        perror("Sending message error");
                        break;
                    }
                }
                break;
            }
            case 2:
            {
                //читаем сообщение из очереди
                if (mq_receive(ds, new_text, SIZE, &prio_recv) == -1)
                {
                    printf("\nНет сообщений, доступных для получения\n");
                    perror("cannot receive");
                    break;
                }

                //проверяем равен ли приоритет 2(для отправки сообщения)
                if (prio_recv == 2)
                {
                    cnt_1 = 0;
                    //отправляем всем клиентам сообщение
                    while (personid[cnt_1] != 0)
                    {
                        prio_send = personid[cnt_1];

                        if (mq_send(ds, new_text, strlen(new_text)+1, prio_send) == -1)
                        {
                            perror("Sending message error");
                            break;
                        }
                        cnt_1++;
                    }
                    printf("\nСообщения отправлены всем пользователям чата");
                    break;
                }
                else
                {
                    //если приоритет не 2, то отправляем сообщение обратно в очередь
                    printf("\nПрочитано сообщение для клиента");
                    if (mq_send(ds, new_text, strlen(new_text)+1, prio_recv) == -1)
                    {
                        perror("Sending message error");
                        break;
                    }
                    break;
                }
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

                if (mq_close(ds) == -1)
                {
                    perror("Closing queue error");
                }

                if (mq_unlink(QUEUE_NAME) == -1)
                {
                    perror("Removing queue error");
                }

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