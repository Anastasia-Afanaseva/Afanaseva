#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#include <errno.h>
#include "funk.h"
#define QUEUE_NAME "/my_queue"
#define SIZE 10

//функция для получения сообщения
int send_mess(int PRIORITY, int ds)
{
    int y;
    char str[10] = {0};
    //посылается сообщение
    printf("\nВведите сообщение для отправки: ");
    memset(str, 0, sizeof(str));
    getchar();
    fgets(str, sizeof(str), stdin);

    if (mq_send(ds, str, strlen(str) + 1, PRIORITY) == -1)
    {
        perror("Sending message error");
        return 0;
    }

    printf("Sending message: %s \n", str);

    return 1;
}

//функция получения сообщения
int recieve_mes(int PRIORITY, int ds)
{
    int prio;
    char new_text[SIZE] = {0};
    //читаем первое сообщение в первой очереди
    if (mq_receive(ds, new_text, SIZE, &prio) == -1)
    {
        if (errno == EAGAIN)
        {
            printf("\nНет сообщений, доступных для получения\n");
            return 1;
        }

        perror("cannot receive");
        return -5;
    }
    //если приоритет полученного сообщения равен приоритету читающего
    //то отправляем полученное сообщение обратно в очередь, чтобы их прочитал собеседник
    if (prio == PRIORITY)
    {
        if (mq_send(ds, new_text, strlen(new_text) + 1, PRIORITY) == -1)
        {
            perror("Sending message error");
            return -5;
        }

        printf("\nНепрочитанное сообщение для собеседника");
        return 0;
    }
    //если сообщение принимает "нужный" собеседник, то читаем и выводим
    else
    {
        printf("Receiving message: %s\n", new_text);
        return 0;
    }
}
