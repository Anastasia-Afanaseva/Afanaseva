#include <stdio.h>
#include <stdlib.h>
#include "funk.h"

extern struct Item* head;
extern struct Item* head_end;

//Добавление элемента
struct Item* Insert(int num) 
{
    struct Item* new_item = malloc(sizeof(struct Item));
    struct Item* tmp;
    if (new_item == NULL)
    {
        printf("\nНе выделилась память для структуры");
        return NULL;
    }
    new_item->value = num;
    if (head == NULL)
    {
        return new_item;
    }
    if (new_item->value < head->value)
    {
        new_item->next = head;
        return new_item;
    }
        tmp = head;
        while (tmp->next != NULL)
        {
            if (new_item->value < tmp->next->value)
            {
                new_item->next = tmp->next;
                tmp->next = new_item;
                break;
            }
            else
            {
                tmp = tmp->next;
            }
        }
    tmp->next = new_item;
    return head;
}
//Функция перехода к следующему элементу
struct Item* deleteFromStart(struct Item* head) 
{
    struct Item* item = head;
    if (item != NULL) 
    {
        head = head->next;
    }
    return head;
}
//Функция удаления элемента
struct Item* deleteValue(int value, struct Item* head) 
{
    struct Item* prev = head;
    struct Item* item;
    if (head == NULL) 
    {
        return NULL;
    }
    if (head->value == value) 
    {
        item = head;
        head = head->next;
        return head;
    }
    while (prev->next != NULL) 
    {
        if (prev->next->value == value) 
        {
            item = prev->next;
            prev->next = prev->next->next;
            return head;
        }
        else 
        {
            prev = prev->next;
        }
    }
    return head;
}
//Функция извлечения
struct Item* extraction(int prior)
{
    if (head == NULL)
    {
        printf("\nНет ни одного пакета в очереди");
        return head_end;
    }
    struct Item* tmp = head;
    struct Item* tmp_end = head_end;
    if (prior == 0)
    {
        if (head_end == NULL)
        {
            head_end = head;
            head = deleteFromStart(head);
            head_end->next = NULL;
            return head_end;
        }
        while (tmp_end->next != NULL)
        {
            tmp_end = tmp_end->next;
        }
        tmp_end->next = head;
        head = deleteFromStart(head);
        tmp->next = NULL;
        return head_end;
    }
    else if (prior > 0)
    {
        while (tmp->next != NULL)
        {
            if (tmp->value == prior)
            {
                break;
            }
            tmp = tmp->next;
        }
        if (tmp->value == prior)
        {
            if (head_end == NULL)
            {
                head_end = tmp;
                head = deleteValue(prior, head);
                head_end->next = NULL;
                return head_end;
            }
            while (tmp_end->next != NULL)
            {
                tmp_end = tmp_end->next;
            }
            tmp_end->next = tmp;
            head = deleteValue(prior, head);
            tmp->next = NULL;
            return head_end;
        }
        else
        {
            printf("\nНет пакета с приоритетом %d", prior);
            return head_end;
        }
    }
    else
    {
        prior = -prior;
        while (tmp->next != NULL)
        {
            if (tmp->value > prior)
            {
                break;
            }
            tmp = tmp->next;
        }
        if (tmp->value > prior)
        {
            if (head_end == NULL)
            {
                head_end = tmp;
                head = deleteValue(tmp->value, head);
                head_end->next = NULL;
                return head_end;
            }
            while (tmp_end->next != NULL)
            {
                tmp_end = tmp_end->next;
            }
            tmp_end->next = tmp;
            head = deleteValue(tmp->value, head);
            tmp->next = NULL;
            return head_end;
        }
        else
        {
            printf("\nНет пакета с приоритетом большим, чем %d", prior);
            return head_end;
        }
    }
}
//Функция удаления списка
struct Item* deleteList(struct Item* head) 
{
    for(struct Item* item = head; item != NULL; item = head) 
    {
        head = head->next;
        free(item);
    }
    return head;
}
//Функция печати списка
void printList(struct Item* h) 
    {
    if (h == NULL)
    {
        printf("\nНет ни одного элемента в списке");
        return;
    }
    for(struct Item* item = h; item != NULL; item = item->next) 
    {
        printf("\n%d ", item->value); 
    }
    printf("\n");
}
