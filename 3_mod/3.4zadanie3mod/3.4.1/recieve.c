/* Прием сообщения из очереди */
#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#define QUEUE_NAME "/my_queue"
#define SIZE 10

int main()
{
    mqd_t ds;
    char new_text[SIZE];
    struct mq_attr attr, old_attr;
    int prio;

    if ((ds = mq_open(QUEUE_NAME, O_RDWR | O_NONBLOCK, 0666, NULL)) == (mqd_t)-1)
    {
        perror("Creating queue error");
        return -1;
    }

    while(atoi(new_text) != 255)
    {
        if (mq_receive(ds, new_text, SIZE, &prio) == -1)
        {
            perror("cannot receive");
            return -1;
        }

        printf("Message: %s\n", new_text);
    }

    if (mq_close(ds) == -1)
    {
        perror("Closing queue error");
    }

    if (mq_unlink(QUEUE_NAME) == -1)
    {
        perror("Removing queue error");
    }

    return 0;
}