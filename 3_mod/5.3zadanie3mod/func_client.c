#include "func_client.h"

//функция обработки ошибок
void error(const char *msg) 
{
    perror(msg);
    exit(0);
}

void recv_send(int my_sock)
{
    int n, cnt = 0, opt;
    char buff[1024];

    n = recv(my_sock, &buff, sizeof(buff) - 1, 0);
    printf("S=>C:%s", buff);
    printf("\nВведите номер необходимой функции:"
            "\n1 - Сложение"
            "\n2 - Вычитание"
            "\n3 - Умножение"
            "\n4 - Деление\n");
    printf("S<=C:");
    scanf("\n%d",&opt);

    switch(opt)
    {
        case 1:
        {
            send(my_sock, "1", strlen("1"), 0);
            break;
        }
        case 2:
        {
            send(my_sock, "2", strlen("2"), 0);
            break;
        }
        case 3:
        {
            send(my_sock, "3", strlen("3"), 0);
            break;
        }
        case 4:
        {
            send(my_sock, "4", strlen("4"), 0);
            break;
        }
        default:
        {
            printf("\nНекорректно введен номер функции");
            exit(0);
        }
    }

    // Шаг 3 - чтение и передача сообщений
    while (cnt != 3)
    {
        cnt++;
        n = recv(my_sock, &buff, sizeof(buff) - 1, 0);
        buff[n] = 0;
        // выводим на экран
        printf("S=>C:%s", buff);

        //выход после получения результата
        if (cnt == 3)
        {
            // Корректный выход
            printf("Exit...");
            close(my_sock);
            exit(0);
        }

        // чтение пользовательского ввода с клавиатуры
        printf("S<=C:");
        scanf("%s", buff);

        // проверка на "quit"(клиент может сам завершить)
        if (!strcmp(buff, "quit"))
        {
            // Корректный выход
            printf("Exit...");
            close(my_sock);
            exit(0);
        }

        // передача строки клиента серверу
        send(my_sock, buff, strlen(buff), 0);
        
    }

    printf("\nrecv error");
    close(my_sock);
    exit(0);
}

