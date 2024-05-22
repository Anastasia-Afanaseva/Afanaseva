#include "func_serv.h"

// количество активных пользователей
int nclients = 0;

int main(int argc, char* argv[])
{
    fd_set master;/* главный список дескрипторов файлов */
    fd_set read_fds;/* список дескрипторов временных файлов для select() */
    int fdmax;/* максимальное количество файловых дескрипторов */
    char buf[1024];
    int newsockfd, listener;//дескрипторы сокетов
    int portno; // номер порта
    socklen_t clilen;//размер адреса клиента типа socklen_t
    struct sockaddr_in serv_addr, cli_addr;//структура сокета сервера и клиента

    printf("TCP SERVER DEMO\n");

    //ошибка в случае если мы не указали порт
    if (argc < 2)
    {
        fprintf(stderr, "\nВведите номер порта в аргументах запуска\n");
        exit(1);
    }

    /* получаем слушателя */
    if((listener = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("\nОшибка создания сокета!");
        exit(1);
    }

    FD_ZERO(&master);
    FD_ZERO(&read_fds);

    //связывание сокета
    bzero((char*) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(listener, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        error("\nОшибка bind");
        exit(1);
    }

    //ожидание подключений, размер очереди - 10
    if(listen(listener, 10) == -1)
    {
        perror("\nОшибка listen");
        exit(1);
    }

    FD_SET(listener, &master);
    fdmax = listener;

    //извлекаем сообщение из очереди (цикл извлечения запросов на подключение)
    while (1)
    {
        read_fds = master;
        if(select(fdmax+1, &read_fds, NULL, NULL, NULL) == -1)
        {
            perror("\nОшибка select()");
            exit(1);
        }

        for(int i = 0; i <= fdmax; i++)
        {
            if(FD_ISSET(i, &read_fds))
            {
                if(i == listener)
                {
                    clilen = sizeof(cli_addr);

                    // Подключился новый клиент
                    if ((newsockfd = accept(listener, (struct sockaddr *)&cli_addr, &clilen)) < 0)
                    {
                        error("\nОшибка accept");
                    }
                    else
                    {
                        nclients++;
                        // вывод сведений о клиенте
                        struct hostent *hst;
                        hst = gethostbyaddr((char *)&cli_addr.sin_addr, 4, AF_INET);
                        printf("+%s [%s] new connect!\n",(hst) ? hst->h_name : "Unknown host",(char*)inet_ntoa(cli_addr.sin_addr));
                        print_users();
                        FD_SET(newsockfd, &master);

                        if(newsockfd > fdmax)
                        {
                            fdmax = newsockfd;
                        }
                    }
                }
                else
                {
                    dostuff(i);
                    nclients--; // уменьшаем счетчик активных клиентов
                    printf("\n-disconnect\n");
                    print_users();
                    close(i);
                    FD_CLR(i, &master);
                }
            }
        }
    }

    return 0;
}