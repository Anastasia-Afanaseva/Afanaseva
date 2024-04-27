/* Отправка сообщения в очередь */
#include <stdio.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>
#define QUEUE_NAME "/my_queue"
#define PRIORITY 1
#define SIZE 5

int main()
{
    int y;
    mqd_t ds;
    char str[10];
    struct mq_attr queue_attr;
    queue_attr.mq_maxmsg = 10;
    queue_attr.mq_msgsize = SIZE;

    if(mq_unlink(QUEUE_NAME) == 0)
    {
        fprintf(stdout, "Message queue %s removed from system.\n", QUEUE_NAME);
    }

    if ((ds = mq_open(QUEUE_NAME, O_CREAT | O_RDWR |O_NONBLOCK , 0666, &queue_attr)) == (mqd_t)-1)
    {
        perror("Creating queue error");
        return -1;
    }

    for (int i = 0; i < 2; i++)
    {
        y = 0;
        memset(str, 0, sizeof(str));
        y += sprintf(str + y, "%d", rand()%100);

        if (mq_send(ds, str, strlen(str)+1, PRIORITY) == -1)
        {
            perror("Sending message error");
            return -1;
        }
        printf("Message: %s \n", str);
    }

    y = 0;
    memset(str, 0, sizeof(str));
    y += sprintf(str + y, "%d", 255);

    if (mq_send(ds, str, strlen(str), PRIORITY) == -1)
    {
        perror("Sending message error");
        return -1;
    }

    printf("Message: %s\n", str);

    if (mq_close(ds) == -1)
    {
        perror("Closing queue error");
    }

    return 0;
}