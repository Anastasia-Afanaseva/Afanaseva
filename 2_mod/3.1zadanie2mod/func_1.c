#include <stdio.h>
#include <string.h>
#include "func_1.h"

//проверка состоит строка из цифр или из символов -rwx
int check_number_or_letters(char *string)
{
    int cnt = 0, j = 0, m = 0;
    char tmp[5] = {};
    //зануляем последний символ если он равен пропуску строки
    int size = strlen(string);
    if (string[size - 1] == '\n')
    {
        string[size - 1] = '\0';
        size = size - 1;
    }
    if (size == 3)
    {
    // проверка состоит ли стрка из цифр
    for (int i = 0; i < size; i++)
    {
        if (((string[i] >= '0') && (string[i] <= '9')) || (string[i] == '\0'))
        {
         cnt++;
        }
    }
    if (cnt == size)
        return 1;
    }
    else if (size == 9)
    {
        cnt = 0;    
        while (j != size)
        {
            if (((string[j] == 'r') || (string[j] == '-')) && (m == 0))
            {
                m++;
            }
            else if (((string[j] == 'w') || (string[j] == '-')) && (m == 1))
            {
                m++;
            }
            else if (((string[j] == 'x') || (string[j] == '-')) && (m == 2))
            {
                m = 0;
                cnt++;
            }
            else return 0;
        j++;
        }
    }
    else 
        return 0;
    return -1;
}
//перевод цифрового в битовое представление
void transform_number(char *string, char *number)
{
    //перевод строки шлюза в массив чисел
    int size = strlen(string);
    int i = 0, j = 0;
    while (i != size)
    {
        if (string[i] > '7')
        {
            printf("\n\tНекорректно введено цифровое представление маски прав доступа");
            return;
        }
        i++;
    }

    for (int i = 0; i < size; i++)
    {
        if (string[i] == '0')
        {
            number[j] = '0';
            j++;
            number[j] = '0';
            j++;
            number[j] = '0';
            j++;
        }
        else if (string[i] == '1')
        {
            number[j] = '0';
            j++;
            number[j] = '0';
            j++;
            number[j] = '1';
            j++;
        }
        else if (string[i] == '2')
        {
            number[j] = '0';
            j++;
            number[j] = '1';
            j++;
            number[j] = '0';
            j++;;
        }
        else if (string[i] == '3')
        {
            number[j] = '0';
            j++;
            number[j] = '1';
            j++;
            number[j] = '1';
            j++;;
        }
        else if (string[i] == '4')
        {
            number[j] = '1';
            j++;
            number[j] = '0';
            j++;
            number[j] = '0';
            j++;
        }
        else if (string[i] == '5')
        {
            number[j] = '1';
            j++;
            number[j] = '0';
            j++;
            number[j] = '1';
            j++;
        }
        else if (string[i] == '6')
        {
            number[j] = '1';
            j++;
            number[j] = '1';
            j++;
            number[j] = '0';
            j++;
        }
        else if (string[i] == '7')
        {
            number[j] = '1';
            j++;
            number[j] = '1';
            j++;
            number[j] = '1';
            j++;
        }
    }
    if (number[strlen(number) - 1] == '\n')
    {
        number[strlen(number)- 1] = '\0';
    }
    printf("\n\tБитовое представление маски прав доступа: %s", number);
}
//перевод буквенного представления в битовое
void transform_letters(char *string, char *letter)
{
    int i = 0;
    while (i != strlen(string))
    {
        if ((string[i] == 'r') || (string[i] == 'w') || (string[i] == 'x'))
        {
            letter[i] = '1';
        }
        else 
        {
            letter[i] = '0';
        }
        i++;
    }
    int size = strlen(letter);
    if (letter[size - 1] == '\n')
    {
        letter[size - 1] = '\0';
        size = size - 1;
    }

    printf("\n\tБитовое представление маски прав доступа: %s", letter);
}