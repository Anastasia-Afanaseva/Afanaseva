#include <stdio.h>
#include "btree.h"
#include <stdlib.h>

btree_t *root = NULL;

int main()
{ 
    int opt;
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
                add_struct();
                break;
            }
            case 2:
            {
                del();
                break;
            }
            case 3:
            {
                change();
                break;
            }
            case 4:
            {
                show();
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