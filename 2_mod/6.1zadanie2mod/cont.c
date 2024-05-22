#include <stdio.h>
#include <string.h>
#include "cont.h"

void add_cont(cont_t *cont)
{
    for (int i = 0; i < 5; i++)
    {
        printf("\tВведите номер телефона:\n");
        if ((fgets(cont->phone[i], 30, stdin) == NULL)
        || (cont->phone[i][0] == '\n'))
            break;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("\tВведите почтовый адрес:\n");
        if ((fgets(cont->mail[i], 30, stdin) == NULL)
        || (cont->mail[i][0] == '\n'))
            break;
    }

    return;
}
void show_cont(cont_t *cont)
{
    for (int j = 0; j < 5; j++)
    {
        if ((strlen(cont->phone[j]) == 0) || (cont->phone[j][0] == '\n'))
            break;
        else
        {
            int size = strlen(cont->phone[j]) - 1;
            if (cont->phone[j][size] == '\n')
            cont->phone[j][size] = 0;
            printf("\t%s", cont->phone[j]);
        }
    }

    for (int j = 0; j < 5; j++)
    {
        if ((strlen(cont->mail[j]) == 0) || (cont->mail[j][0] == '\n'))
            break;
        else
        {
            int size = strlen(cont->mail[j]) - 1;
            if (cont->mail[j][size] == '\n')
            cont->mail[j][size] = 0;
            printf("\t%s", cont->mail[j]);
        }
    }
}