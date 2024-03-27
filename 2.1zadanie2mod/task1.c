#include <stdio.h>
#include <string.h>
#include "info_all.h"
extern info_all_t info[10];

int check_place(info_all_t *info)
{
    for (int i = 0; i < sizeof(info); i++)
    {
        if (((strlen(info[i].person.firstname) == 0) || (strlen(info[i].person.lastname) == 0))
        && ((info[i].person.firstname[0] != '\n') || (info[i].person.lastname[0] != '\n')))
            return i; 
    }
    return -1; 
}

int add_person(info_all_t *info)
{
    printf("\tВведите имя:\n");
    getchar();
    if ((fgets(info->person.firstname, 20, stdin) == NULL)
       || (info->person.firstname[0] == '\n'))
    {
        printf("\tНеобходимо ввести имя\n");
        return -1;
    }

    printf("\tВведите фамилию:\n");
    if ((fgets(info->person.lastname, 20, stdin) == NULL)
    || (info->person.lastname[0] == '\n'))
    {
        printf("\tНеобходимо ввести фамилию\n");
        return -1;
    }

    int size = strlen(info->person.firstname) - 1;
    info->person.firstname[size] = 0;
    size = strlen(info->person.lastname) - 1;
    info->person.lastname[size] = 0;
    return 0;
}

void add_work(info_all_t *info)
{
    printf("\tВведите место работы:\n");
    fgets(info->work.place, 30, stdin);
    if ((strlen(info->work.place) != 0) && (info->work.place[0] != '\n'))
    {
        printf("\tВведите должность:\n");
        fgets(info->work.title, 30, stdin);
    }
    return;
}

void add_cont(info_all_t *info)
{
    for (int i = 0; i < 5; i++)
    {
        printf("\tВведите номер телефона:\n");
        if ((fgets(info->cont.phone[i], 30, stdin) == NULL)
        || (info->cont.phone[i][0] == '\n'))
            break;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("\tВведите почтовый адрес:\n");
        if ((fgets(info->cont.mail[i], 30, stdin) == NULL)
        || (info->cont.mail[i][0] == '\n'))
            break;
    }

    return;
}

void add_society(info_all_t *info)
{
    printf("\tВведите ссылку на телеграм:\n");
    fgets(info->society.telegram, 128, stdin);

    printf("\tВведите ссылку ВКонтакте:\n");
    fgets(info->society.vk, 128, stdin);

    printf("\tВведите ссылку WhatsApp:\n");
    fgets(info->society.whatsapp, 128, stdin);

    printf("\tВведите ссылку на facebook:\n");
    fgets(info->society.facebook, 128, stdin);
    return;
}

void add(void)
{
    int id = check_place(info);
    if (id < 0)
    {
        printf("\tБольше нет места для добавления\n");
        return;
    }
    if (add_person(&info[id]) < 0)
    {
        printf("\tНе введены фамилия или имя\n");
        return;
    }
    add_work(&info[id]);
    add_cont(&info[id]);
    add_society(&info[id]);
    return;
}

void id_name_fam(info_all_t *info)
{
    int id = check_place(info);
    int size;
    if (id == -1)
        size = 10;
    else size = id;

    for (int i = 0; i < size; i++)
    {
        printf("\n\t%d %s", i + 1, info[i].person.firstname);
        printf(" %s\n", info[i].person.lastname);
    }

    return;
}

void del(info_all_t *info)
{
    int size_1 = sizeof(info_all_t);
    int opt_1, size;
    int id = check_place(info);
    if (id == -1)
        size = 10;
    else size = id;
    if (size == 0) 
    {
        printf("\tНет контактов в списке\n");
        return;
    }
    printf("\tВыберите номер пользователя для удаления из списка:\n");
    id_name_fam(info);
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

void change(info_all_t *info)
{
    int opt_1, opt_2;
    int id = check_place(info);
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
    id_name_fam(info);
    scanf("\t%d", &opt_1);
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
    scanf("%d", &opt_2);

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
            add_work(&info[opt_1 - 1]);
            break;
        }
        case 3:
        {
            getchar();
            add_cont(&info[opt_1 - 1]);
            break;
        }
        case 4:
        {
            getchar();
            add_society(&info[opt_1 - 1]);
            break;
        }
        default:
        {
            printf("\n\tНекорректно введена позиция для редактирования\n");
        }
    }
}

void show(info_all_t *info)
{
    printf("\tИнформация обо всех пользователях:\n");
    int id = check_place(info);
    int size;
    if (id == -1)
        size = 10;
    else size = id;

    if (size == 0)
        printf("\tНет ни одного контакта\n");

    for (int i = 0; i < size; i++)
    {
        printf("\n\t%d %s", i + 1, info[i].person.firstname);
        printf(" %s", info[i].person.lastname);

        if ((strlen(info[i].work.place) != 0) && (info[i].work.place[0] != '\n'))
        {
            int size = strlen(info[i].work.place) - 1;
            if (info[i].work.place[size] == '\n')
                info[i].work.place[size] = 0;
            printf("\t%s", info[i].work.place);
        }

        if ((strlen(info[i].work.title) != 0) && (info[i].work.title[0] != '\n'))
        {
            int size = strlen(info[i].work.title) - 1;
            if (info[i].work.title[size] == '\n')
                info[i].work.title[size] = 0;
            printf("\t%s", info[i].work.title);
        }

        for (int j = 0; j < 5; j++)
        {
            if ((strlen(info[i].cont.phone[j]) == 0) || (info[i].cont.phone[j][0] == '\n'))
                break;
            else
            {
                int size = strlen(info[i].cont.phone[j]) - 1;
                if (info[i].cont.phone[j][size] == '\n')
                    info[i].cont.phone[j][size] = 0;
                printf("\t%s", info[i].cont.phone[j]);
            }
        }

        for (int j = 0; j < 5; j++)
        {
            if ((strlen(info[i].cont.mail[j]) == 0) || (info[i].cont.mail[j][0] == '\n'))
                break;
            else
            {
                int size = strlen(info[i].cont.mail[j]) - 1;
                if (info[i].cont.mail[j][size] == '\n')
                    info[i].cont.mail[j][size] = 0;
                printf("\t%s", info[i].cont.mail[j]);
            }
        }

        if ((strlen(info[i].society.telegram) != 0) && (info[i].society.telegram[0] != '\n'))
        {
            int size = strlen(info[i].society.telegram) - 1;
            if (info[i].society.telegram[size] == '\n')
                info[i].society.telegram[size] = 0;
            printf("\t%s", info[i].society.telegram);
        }

        if ((strlen(info[i].society.vk) != 0) && (info[i].society.vk[0] != '\n'))
        {
            int size = strlen(info[i].society.vk) - 1;
            if (info[i].society.vk[size] == '\n')
                info[i].society.vk[size] = 0;
            printf("\t%s", info[i].society.vk);
        }

        if ((strlen(info[i].society.whatsapp) != 0) && (info[i].society.whatsapp[0] != '\n'))
        {
            int size = strlen(info[i].society.whatsapp) - 1;
            if (info[i].society.whatsapp[size] == '\n')
                info[i].society.whatsapp[size] = 0;
            printf("\t%s", info[i].society.whatsapp);
        }
            
        if ((strlen(info[i].society.facebook) != 0) && (info[i].society.facebook[0] != '\n'))
        {
            int size = strlen(info[i].society.facebook) - 1;
            if (info[i].society.facebook[size] == '\n')
                info[i].society.facebook[size] = 0;
            printf("\t%s", info[i].society.facebook);
        }
    }

    return;
}