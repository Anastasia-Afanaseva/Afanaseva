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
        printf("%d Пользователь on-line\n",nclients);
    }
    else
    {
        printf("Нет пользователей on-line\n");
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

    if ((bytes_recv = read(sock,&buff,sizeof(buff))) < 0)
    {
        printf("\nОшибка read");
        return;
    }

    num_func = atoi(buff);
    memset(buff,0,sizeof(buff));

    //отправляем клиенту сообщение
    if (write(sock, str1, sizeof(str1)) < 0)
    {
        printf("\nОшибка write");
        return;
    }

    //обработка первого параметра
    if ((bytes_recv = read(sock,&buff,sizeof(buff))) < 0)
    {
        error("Ошибка read");
        return;
    }

    a = atoi(buff); // преобразование первого параметра в int
    memset(buff,0,sizeof(buff));
    
    if (write(sock,str2,sizeof(str2)) < 0)
    {
        printf("\nОшибка write");
        return;
    }

    if ((bytes_recv = read(sock,&buff,sizeof(buff))) < 0)
    {
        printf("\nОшибка read");
        return;
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
        if (b == 0)
        {
            printf("\n На 0 делить нельзя");
            return;
        }
        else
        {
            m = division(a,b);
            snprintf(buff, sizeof(buff), "%.3f", m);
        }
    }

    buff[strlen(buff)] = '\n';//добавление к сообщению символа конца строки
    //отправляем клиенту результат

    if (write(sock,buff, sizeof(buff)) < 0)
    {
        printf("\nОшибка write");
        return;
    }

    return;
}
