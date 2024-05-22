#include <stdio.h>
#include <string.h>
#include "info_all.h"
#define CNT 10
info_all_t info[CNT];

int check_place(void)
{
    for (int i = 0; i < CNT; i++)
    {
        if (check_person(&info[i].person) == 1)
            return i; 
    }
    
    return -1; 
}

void add(void)
{
    int id = check_place();
    if (id < 0)
    {
        printf("\tБольше нет места для добавления\n");
        return;
    }
    if (add_person(&info[id].person) < 0)
    {
        printf("\tНе введены фамилия или имя\n");
        return;
    }
    add_work(&info[id].work);
    add_cont(&info[id].cont);
    add_society(&info[id].society);
    return;
}

void del(void)
{
    int size_1 = sizeof(info_all_t);
    int opt_1, size;
    int id = check_place();
    if (id == -1)
        size = 10;
    else size = id;
    if (size == 0) 
    {
        printf("\tНет контактов в списке\n");
        return;
    }
    printf("\tВыберите номер пользователя для удаления из списка:\n");

    for (int i = 0; i < size; i++)
    {
        printf("\n\t%d", i + 1);
        show_person(&info[i].person);
    }
    scanf("\t%d", &opt_1);
    if ((opt_1 > size || opt_1 < 1))
    {
        printf("\tНет такого номера в списке для удаления\n");
        return;
    }
    
    for (int i = opt_1; i < size; i++)
    {
        memcpy(&info[i - 1], &info[i], size_1);
    }

    memset(&info[size - 1], 0, size_1);
    return;
}

void change(void)
{
    int opt_1, opt_2;
    int id = check_place();
    int size;
    if (id == -1)
        size = 10;
    else size = id;
    if (size == 0) 
    {
        printf("\tНет контактов в списке\n");
        return;
    }
    printf("\tВыберите номер пользователя для редактирования:\n");
    for (int i = 0; i < size; i++)
    {
        printf("\n\t%d", i + 1);
        show_person(&info[i].person);
    }
    
    scanf("\n\t%d", &opt_1);
    if ((opt_1 > size || opt_1 < 1))
    {
        printf("\tНет такого номера в списке для редактирования\n");
        return;
    }
    printf("\tВыберите номер позиции для редактирования:\n"
            "\t1 - Имя/фамилию\n"
            "\t2 - Место работы/должность\n"
            "\t3 - Номера телефонов/Почтовые адреса\n"
            "\t4 - Ссылки на социальные сети\n");
    scanf("\n%d", &opt_2);

    switch(opt_2)
    {
        case 1:
        {
            add_person(&info[opt_1 - 1].person);
            break;
        }
        case 2:
        {
            getchar();
            add_work(&info[opt_1 - 1].work);
            break;
        }
        case 3:
        {
            getchar();
            add_cont(&info[opt_1 - 1].cont);
            break;
        }
        case 4:
        {
            getchar();
            add_society(&info[opt_1 - 1].society);
            break;
        }
        default:
        {
            printf("\n\tНекорректно введена позиция для редактирования\n");
        }
    }
}

void show(void)
{
    printf("\tИнформация обо всех пользователях:\n");
    int id = check_place();
    int size;
    if (id == -1)
        size = 10;
    else size = id;

    if (size == 0)
        printf("\tНет ни одного контакта\n");

    for (int i = 0; i < size; i++)
    {
        printf("\n\t%d ", i + 1);
        show_person(&info[i].person);
        show_work(&info[i].work);
        show_cont(&info[i].cont);
        show_society(&info[i].society);
    }

    return;
}