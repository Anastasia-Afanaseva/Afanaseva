#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <errno.h>
#define QUEUE_NAME "/my_queue"
#define SIZE 10
#include "funk.h"

int main(int argc, char *argv[])
{
    int opt, prio, cnt, ret;
    mqd_t ds;
    struct mq_attr queue_attr;
    queue_attr.mq_maxmsg = SIZE;
    queue_attr.mq_msgsize = 10;

    //проверка аргументов запуска на корректность
    if ((argc == 1) || (atoi(argv[1]) <= 0))
    {
        printf("\nНекорректно указан приоритет");
        exit(0);
    }

    int PRIORITY = atoi(argv[1]);
    //создание очереди
    if ((ds = mq_open(QUEUE_NAME, O_CREAT | O_RDWR | O_NONBLOCK, 0666, &queue_attr)) == (mqd_t)-1)
    {
        perror("Creating queue error");
        exit(0);
    }
    //бесконечный цикл
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
                ret = send_mess(PRIORITY,ds);
                if (ret == 0)
                {
                    exit(0);
                }
                break;
            }
            case 2:
            {
                //получение сообщений
                cnt = recieve_mes(PRIORITY,ds);

                if ((cnt != 1) && (cnt != 0))
                {
                    printf("\nНет сообщений, доступных для получения\n");
                }
                else if (cnt < -1)
                {
                    exit(0);
                }

                break;
            }
            case 3:
            {
                //удаление связи между дискриптором и очередью
                if (mq_close(ds) == -1)
                {
                    perror("Closing queue error");
                }

                //удаление имени очереди сообщений
                if(mq_unlink(QUEUE_NAME) == 0)
                {
                    fprintf(stdout, "Message queue %s removed from system.\n", QUEUE_NAME);
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