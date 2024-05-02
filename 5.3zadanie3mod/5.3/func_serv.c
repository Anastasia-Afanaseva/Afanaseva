#include "func_serv.h"

extern int nclients;
// функция обработки ошибок
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// печать количества активных пользователей
void print_users()
{
    if(nclients)
    {
        printf("%d user on-line\n",nclients);
    }
    else
    {
        printf("No User on-line\n");
    }
}

//функция сложения
int summ(int a, int b)
{
    return a + b;
}

//функция вычитания
int substr(int a, int b)
{
    return a - b;
}

//функция умножения
int multipli(int a, int b)
{
    return a * b;
}

//функция деления
float division(int a, int b)
{
    return (float)a / b;
}

//функция получения и отправки сообщений клиенту
void dostuff (int sock)
{
    float m = 0;
    int bytes_recv; // размер принятого сообщения
    int a = 0, b = 0, num_func = 0; // переменные для myfunc
    char buff[1024] = {0};
    #define str1 "Enter 1 parameter\r\n"
    #define str2 "Enter 2 parameter\r\n"
    #define str3 "Enter function\r\n"
    write(sock, str3, sizeof(str3));
    bytes_recv = read(sock,&buff,sizeof(buff));
    num_func = atoi(buff);
    memset(buff,0,sizeof(buff));
    //отправляем клиенту сообщение
    write(sock, str1, sizeof(str1));
    //обработка первого параметра
    bytes_recv = read(sock,&buff,sizeof(buff));

    if (bytes_recv < 0)
    {
        error("ERROR reading from socket");
        exit(0);
    }

    a = atoi(buff); // преобразование первого параметра в int
    memset(buff,0,sizeof(buff));
    write(sock,str2,sizeof(str2));
    bytes_recv = read(sock,&buff,sizeof(buff));

    if (bytes_recv < 0)
    {
        error("ERROR reading from socket");
        exit(0);
    }

    b = atoi(buff); // преобразование второго параметра в int
    memset(buff,0,sizeof(buff));

    if (num_func == 1)
    {
        a = summ(a,b);
        snprintf(buff, sizeof(buff), "%d", a);
    }
    else if (num_func == 2)
    {
        a = substr(a,b);
        snprintf(buff, sizeof(buff), "%d", a);
    }
    else if (num_func == 3)
    {
        a = multipli(a,b);
        snprintf(buff, sizeof(buff), "%d", a);
    }
    else if (num_func == 4)
    {
        m = division(a,b);
        snprintf(buff, sizeof(buff), "%.3f", m);
    }

    buff[strlen(buff)] = '\n';//добавление к сообщению символа конца строки
    //отправляем клиенту результат
    write(sock,buff, sizeof(buff));
    nclients--; // уменьшаем счетчик активных клиентов
    printf("\n-disconnect\n");
    print_users();
    return;
}
