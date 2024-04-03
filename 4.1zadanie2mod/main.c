#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "item.h"

int main()
{ 
    int opt;
    struct Item* head = NULL;

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
                exit(0);
            }
            default:
            {
                printf("\tВведена некорректная функция\n");
            }
        }
    }
}