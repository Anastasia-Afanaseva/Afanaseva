#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int sockfd; /* Дескриптор сокета */
    int n, len; /* Переменные для различных длин и количества символов */
    char sendline[1000] = {0}, recvline[1000] = {0}; /* Массивы для отсылаемой и принятой строки */
    struct sockaddr_in cliaddr_1, cliaddr_2; /* Структуры для адресов сервера и клиента */
    /* Сначала проверяем наличие второго аргумента в
    командной строке. При его отсутствии ругаемся и прекращаем работу */

    /* Создаем UDP сокет */
    if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror(NULL); /* Печатаем сообщение об ошибке */
        exit(1);
    }

    /* Заполняем структуру для адреса клиента */
    bzero(&cliaddr_1, sizeof(cliaddr_1));
    cliaddr_1.sin_family = AF_INET;
    cliaddr_1.sin_port = htons(52000);
    cliaddr_1.sin_addr.s_addr = htonl(INADDR_ANY);

    /* Настраиваем адрес сокета */
    if(bind(sockfd, (struct sockaddr *) &cliaddr_1, sizeof(cliaddr_1)) < 0)
    {
        perror(NULL);
        close(sockfd); /* По окончании работы закрываем дескриптор сокета */
        exit(1);
    }

    /* Заполняем структуру для адреса собеседника */
    bzero(&cliaddr_2, sizeof(cliaddr_2));
    cliaddr_2.sin_family = AF_INET;
    cliaddr_2.sin_port = htons(51000);

    if(inet_aton("127.0.0.1", &cliaddr_2.sin_addr) == 0)
    {
        printf("Invalid IP address\n");
        close(sockfd); /* По окончании работы закрываем дескриптор сокета */
        exit(1);
    }

    while (1)
    {
        memset(sendline, 0, sizeof(sendline));
        memset(recvline, 0, sizeof(recvline));
        /* Вводим строку, которую отошлем собеседнику */
        printf("Сообщение для отправки => ");
        fgets(sendline, 1000, stdin);

        /* Отсылаем датаграмму */
        if(sendto(sockfd,sendline,strlen(sendline)+1,0,(struct sockaddr *) &cliaddr_2,sizeof(cliaddr_2)) < 0)
        {
            perror(NULL);
            close(sockfd);
            exit(1);
        }

        //Если прощаемся, то отправляем сообщение, закрываем дискриптор сокета, покидаем чат
        if (strncmp("Bye", sendline, strlen("Bye")) == 0)
        {
            /* Отсылаем датаграмму */
            if(sendto(sockfd,sendline,strlen(sendline)+1,0,(struct sockaddr *) &cliaddr_1,sizeof(cliaddr_1)) < 0)
            {
                perror(NULL);
                close(sockfd);
                exit(1);
            }

            close(sockfd);
            exit(1);
        }

        /* Ожидаем ответа и читаем его*/
        if((n = recvfrom(sockfd,recvline,1000,0,(struct sockaddr *) NULL,NULL)) < 0)
        {
            perror(NULL);
            close(sockfd);
            exit(1);
        }

        /*Печатаем пришедший ответ*/
        printf("Присланное сообщение: %s\n", recvline);

        //Проверяем, если собеседник попрощался, то закрываем дискриптор сокета, выходим из чата
        if (strncmp("Bye", recvline, strlen("Bye")) == 0)
        {
            close(sockfd);
            exit(1);
        }
    }

}