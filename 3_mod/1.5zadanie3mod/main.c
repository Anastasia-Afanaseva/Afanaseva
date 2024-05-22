#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "item.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int flags = O_RDWR | O_CREAT;
    int fd = 0;
    if ((fd = open("list.txt", flags, mode)) == -1)
    {
        printf("\n\tНе удалось открыть файл");
        getchar();
        return 0;
    }

    int opt;
    struct Item *head = NULL;
    head = reading_(head, fd);

    while (1)
    {
        printf("\t\nВыберите функцию:\n"
                "\t1 - Добавить пользователя\n"
                "\t2 - Удалить пользователя\n"
                "\t3 - Редактировать пользователя\n"
                "\t4 - Показать всех пользователей\n"
                "\t5 - Завершить\n");

        scanf("%d", &opt);
        switch(opt)
        {
            case 1:
            {
                head = add(head);
                break;
            }
            case 2:
            {
                head = del(head);
                break;
            }
            case 3:
            {
                head = change(head);
                break;
            }
            case 4:
            {
                show(head);
                break;
            }
            case 5:
            {
                if (close(fd) == -1)
                {
                    printf("\n\tПроизошла ошибка закрытия файла");
                    break;
                }

                if ((fd = open("list.txt", O_WRONLY | O_CREAT | O_TRUNC, 0600)) == -1)
                {
                    printf("\n\tНе удалось открыть файл");
                    getchar();
                    return 0;
                }

                head = writing(head, fd);
                if (close(fd) == -1)
                {
                    printf("\n\tПроизошла ошибка закрытия файла");
                    break;
                }

                exit(0);
            }
            default:
            {
                printf("\tВведена некорректная функция\n");
                break;
            }
        }
    }
}
