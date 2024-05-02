#include "func_client.h"

int main(int argc, char *argv[])
{
    int my_sock, portno;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    printf("TCP DEMO CLIENT\n");

    //проверка на корректность аргументов запуска(1 аргумент - IP-адрес, 2 аргумент - порт)
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    // извлечение порта
    portno = atoi(argv[2]);
    // Шаг 1 - создание сокета(возвращает целочисленный номер сокет-дескриптора)
    my_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (my_sock < 0) 
    {
        error("ERROR opening socket");
    }

    // извлечение хоста(server - указатель на структуру узла)
    server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    // заполнение структуры serv_addr
    //устанавливает первые sizeof(serv_addr) байтов области, начинающейся с &serv_addr в нули 
    bzero((char*) &serv_addr, sizeof(serv_addr));
    //семейство протоколов AF_INET - IPv4 протоколы
    serv_addr.sin_family = AF_INET;
    //копирование server->h_length байтов из server->h_addr в &serv_addr.sin_addr.s_addr
    //копирование адреса полученного узла в структуру клиента
    bcopy((char*)server->h_addr, (char *)&serv_addr.sin_addr.s_addr,server->h_length);
    // установка порта, перевод данных из узлового (host) порядка расположения байтов в сетевой(network)
    serv_addr.sin_port = htons(portno);

    // Шаг 2 - установка соединения
    if (connect(my_sock, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        error("ERROR connecting");
    }

    //функция получения от сервера и отправки данных серверу
    recv_send(my_sock);
}
