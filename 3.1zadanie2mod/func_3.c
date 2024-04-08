#include <stdio.h>
#include <string.h>
#include "func_3.h"

//проверка правильности введения команды модификации атрибутов
int check_change(char *str)
{
    int i = 0;
    int size = strlen(str);
    if (str[size - 1] == '\n')
    {
        str[size - 1] = '\0';
        size = size - 1;
    }
    if (size > 3)
        return 0;

    while (i < size)
    {
        if ((i == 0) && ((str[i] == 'a') || (str[i] == 'o') || (str[i] == 'g') || (str[i] == 'u')))
            i++;
        if ((i == 1) && ((str[i] == '+') || (str[i] == '-')))
            i++;
        if ((i == 2) && ((str[i] == 'r') || (str[i] == 'w') || (str[i] == 'x')))
            i++;
        else 
            return 0;
    }
    return 1;
}
//изменение атрибутов маски прав доступа
void edit(char *str, char *doubl)
{
    int i = 0;

    if ((str[0] == 'a') && (str[1] == '+') && (str[2] == 'r'))
    {
        doubl[0] = '1';
        doubl[3] = '1';
        doubl[6] = '1';
        return;
    }
    if ((str[0] == 'a') && (str[1] == '+') && (str[2] == 'w'))
    {
        doubl[1] = '1';
        doubl[4] = '1';
        doubl[7] = '1';
        return;
    }
    if ((str[0] == 'a') && (str[1] == '+') && (str[2] == 'x'))
    {
        doubl[2] = '1';
        doubl[5] = '1';
        doubl[8] = '1';
        return;
    }
    if ((str[0] == 'a') && (str[1] == '-') && (str[2] == 'x'))
    {
        doubl[2] = '0';
        doubl[5] = '0';
        doubl[8] = '0';
        return;
    }
    if ((str[0] == 'a') && (str[1] == '-') && (str[2] == 'w'))
    {
        doubl[1] = '0';
        doubl[4] = '0';
        doubl[7] = '0';
        return;
    }
    if ((str[0] == 'a') && (str[1] == '-') && (str[2] == 'r'))
    {
        doubl[0] = '0';
        doubl[3] = '0';
        doubl[6] = '0';
        return;
    }
    if ((str[0] == 'u') && (str[1] == '+') && (str[2] == 'r'))
    {
        doubl[1] = '1';
        return;
    }
    if ((str[0] == 'u') && (str[1] == '-') && (str[2] == 'r'))
    {
        doubl[0] = '0';
        return;
    }
    if ((str[0] == 'u') && (str[1] == '+') && (str[2] == 'x'))
    {
        doubl[2] = '1';
        return;
    }
    if ((str[0] == 'u') && (str[1] == '-') && (str[2] == 'x'))
    {
        doubl[2] = '0';
        return;
    }
    if ((str[0] == 'u') && (str[1] == '+') && (str[2] == 'w'))
    {
        doubl[1] = '1';
        return;
    }
    
    if ((str[0] == 'u') && (str[1] == '-') && (str[2] == 'w'))
    {
        doubl[1] = '0';
        return;
    }

    if ((str[0] == 'g') && (str[1] == '+') && (str[2] == 'r'))
    {
        doubl[3] = '1';
        return;
    }
    if ((str[0] == 'g') && (str[1] == '-') && (str[2] == 'r'))
    {
        doubl[3] = '0';
        return;
    }
    if ((str[0] == 'g') && (str[1] == '+') && (str[2] == 'x'))
    {
        doubl[5] = '1';
        return;
    }
    if ((str[0] == 'g') && (str[1] == '-') && (str[2] == 'x'))
    {
        doubl[5] = '0';
        return;
    }
    if ((str[0] == 'g') && (str[1] == '+') && (str[2] == 'w'))
    {
        doubl[4] = '1';
        return;
    }
    if ((str[0] == 'g') && (str[1] == '-') && (str[2] == 'w'))
    {
        doubl[4] = '0';
        return;
    }

    if ((str[0] == 'o') && (str[1] == '+') && (str[2] == 'r'))
    {
        doubl[6] = '1';
        return;
    }
    if ((str[0] == 'o') && (str[1] == '-') && (str[2] == 'r'))
    {
        doubl[6] = '0';
        return;
    }
    if ((str[0] == 'o') && (str[1] == '+') && (str[2] == 'x'))
    {
        doubl[8] = '1';
        return;
    }
    if ((str[0] == 'o') && (str[1] == '-') && (str[2] == 'x'))
    {
        doubl[8] = '0';
        return;
    }
    if ((str[0] == 'o') && (str[1] == '+') && (str[2] == 'w'))
    {
        doubl[7] = '1';
        return;
    }
    if ((str[0] == 'o') && (str[1] == '-') && (str[2] == 'w'))
    {
        doubl[7] = '0';
        return;
    }
}
//перевод битового в текстовое представление
void binary_to_letters(char *str)
{
    int cnt = 0;
    char let[10] = {};
    for (int i = 0; i < strlen(str); i++)
    {
        if ((str[i] == '1') && (cnt == 0))
        {
            let[i] = 'r';
            cnt++;
        }
        else if ((str[i] == '1') && (cnt == 1))
        {
            let[i] = 'w';
            cnt++;
        }
        else if ((str[i] == '1') && (cnt == 2))
        {
            let[i] = 'x';
            cnt = 0;
        }
        else 
        {
            let[i] = '-';
            if (cnt == 2)
                cnt = 0;
            else
                cnt++;
        }
    }
    if (let[strlen(let) - 1] == '\n')
        let[strlen(let) - 1] = 0;
    printf("\n\tБуквенное представление прав доступа: %s", let);
}
