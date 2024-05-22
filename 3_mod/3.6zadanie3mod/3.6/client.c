#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#define QUEUE_NAME "/my_queue"
#define SIZE 50

int main()
{
    mqd_t ds;
    char new_text[SIZE];
    int prio_recv, prio_send;

    int opt,cnt = 0,opt_1;
    char str[SIZE];
    int y = 0, type;

    if ((ds = mq_open(QUEUE_NAME, O_RDWR | O_NONBLOCK, 0666, NULL)) == (mqd_t)-1)
    {
        perror("Чат еще не создан");
        return -1;
    }

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

                printf("\nВведите идентификатор:");
                scanf("%d", &opt_1);
                type = opt_1;
                prio_send = 1;
                y = 0;
                memset(str, 0, sizeof(str));
                y += sprintf(str + y, "%d", type);
                printf("\nОтправляю идентификатор %s",str);

                //отправление сообщения с приоритетом 1, в сообщении которого идентификатор клиента
                if (mq_send(ds, str, strlen(str)+1, prio_send) == -1)
                {
                    if (errno == EBADF)
                    {
                        printf("\nЧат закрыт");
                        exit(0);
                    }
                    perror("Sending message error");
                    break;
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

                //отправление сообщения с приоритетом 2
                prio_send = 2;

                printf("\nВведите сообщение для отправки в чат\n");
                memset(str, 0, sizeof(str));
                getchar();
                fgets(str, sizeof(str),stdin);

                if (mq_send(ds, str, strlen(str)+1, prio_send) == -1)
                {
                    if (errno == EBADF)
                    {
                        printf("\nЧат закрыт");
                        exit(0);
                    }
                    perror("Sending message error");
                    break;
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
                if (mq_receive(ds, new_text, SIZE, &prio_recv) == -1)
                {
                    if (errno == EBADF)
                    {
                        printf("\nЧат закрыт");
                        exit(0);
                    }
                    printf("\nНет сообщений, доступных для получения\n");
                    perror("cannot receive");
                    break;
                }

                //провера равен ли приоритет прочитанного сообщения приоритету клиента
                if (prio_recv == type)
                {
                    printf("Сообщение: %s\n", new_text);
                }
                else
                {
                    //приоритет не равен приоритету клиента
                    printf("\nПрочитано сообщение для другого пользователя");
                    if (mq_send(ds, new_text, strlen(new_text)+1, prio_recv) == -1)
                    {
                        if (errno == EBADF)
                        {
                            printf("\nЧат закрыт");
                            exit(0);
                        }
                        perror("Sending message error");
                        break;
                    }
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