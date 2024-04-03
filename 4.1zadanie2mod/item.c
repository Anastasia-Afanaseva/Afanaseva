#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

struct Item* add(struct Item* head) 
{
    struct Item* new_item;
    struct Item* tmp = head;
    
    new_item = malloc(sizeof(item_t));
    if (new_item == NULL)
    {
        printf("Не выделилась память для новой структуры\n");
        return head;
    }
   
    if (add_person(&new_item->info_all.person) < 0)
    {
        printf("\tНе введены фамилия или имя\n");
        return head;
    }
    add_work(&new_item->info_all.work);
    add_cont(&new_item->info_all.cont);
    add_society(&new_item->info_all.society);
    
    if (NULL == head)
    {
        new_item->next = new_item;
        new_item->prev = new_item;
        head = new_item;
        return head;
    }

    do
        {
        if (compare_person(&new_item->info_all.person, &tmp->info_all.person) > 0)
        {
            new_item->next = tmp;
            new_item->prev = tmp->prev;
            tmp->prev->next = new_item;
            tmp->prev = new_item;
            if (tmp == head)
                head =  new_item;
            return head;
        }
        tmp = tmp->next;
        } while (tmp != head);

    new_item->next = tmp;
    new_item->prev = tmp->prev;
    tmp->prev->next = new_item;
    tmp->prev = new_item;
    return head;   
}

struct Item* del(struct Item* head)
{
    struct Item *tmp = head;
    int i = 0, opt_1, k = 1;
    if (head == NULL) 
    {
        printf("\tНет контактов в списке\n");
        return NULL;
    }
    printf("\tВыберите номер пользователя для удаления из списка:\n");
    do
    {
        i++;
        printf("\n\t%d", i);
        show_person(&tmp->info_all.person);
        tmp = tmp->next;
    } while (tmp != head);
    
    scanf("\t%d", &opt_1);
    
    do 
    {
        if(k == opt_1)
        {
            if (tmp->next == tmp)
            {
                free(tmp);
                return NULL;
            }
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        if (tmp == head)
            head = head->next;
        free(tmp);
        return head;
        }
        tmp = tmp->next;
        k++;
    } while (tmp != head);
    printf("\tНет такого номера в списке для удаления\n");
    return head;
}
struct Item* change(struct Item* head)
{
    int opt_1, opt_2, i = 0, k = 1;
    struct Item* tmp = head;
    if (head == NULL) 
    {
        printf("\tНет контактов в списке\n");
        return NULL;
    }
    printf("\tВыберите номер пользователя для редактирования:\n");
    do
    {
        i++;
        printf("\n\t%d", i);
        show_person(&tmp->info_all.person);
        tmp = tmp->next;
    } while (tmp != head);
    
    scanf("\n\t%d", &opt_1);
    if ((opt_1 > i || opt_1 < 1))
    {
        printf("\tНет такого номера в списке для редактирования\n");
        return head;
    }
    printf("\tВыберите номер позиции для редактирования:\n"
            "\t1 - Имя/фамилию\n"
            "\t2 - Место работы/должность\n"
            "\t3 - Номера телефонов/Почтовые адреса\n"
            "\t4 - Ссылки на социальные сети\n");
    scanf("\n%d", &opt_2);

    do 
    {
        if(k == opt_1)
        {
            switch(opt_2)
            {
                case 1:
                {
                    add_person(&tmp->info_all.person);
                    break;
                }
                case 2:
                {
                    getchar();
                    add_work(&tmp->info_all.work);
                    break;
                }
                case 3:
                {
                    getchar();
                    add_cont(&tmp->info_all.cont);
                    break;
                }
                case 4:
                {
                    getchar();
                    add_society(&tmp->info_all.society);
                    break;
                }
                default:
                {
                    printf("\n\tНекорректно введена позиция для редактирования\n");
                }
            }
        } 
        tmp = tmp->next;
        k++;
    }while (tmp != head);
}

void show(struct Item* head)
{
    int i = 0;
    printf("\tИнформация обо всех пользователях:\n");
    struct Item* tmp = head;
    if (head == NULL) 
    {
        printf("\tНет контактов в списке\n");
        return;
    }
    do
    {
        i++;
        printf("\n\t%d ", i);
        show_person(&tmp->info_all.person);
        show_work(&tmp->info_all.work);
        show_cont(&tmp->info_all.cont);
        show_society(&tmp->info_all.society);
        tmp = tmp->next;
    } while (tmp != head);
    return;
}

