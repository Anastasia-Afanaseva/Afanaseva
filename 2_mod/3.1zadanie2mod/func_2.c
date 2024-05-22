#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "func_2.h"

//перевод из битового представления маски прав доступа в цифровое
int binary_to_number(char *str)
{
    int j = 0, t = 0, m = 0;
    int mas[3] = {};
    int num = 0;
    for (int i = 0; i < 9; i++)
    {
        if ((str[i] == '1') && (j == 0))
        {
            t = t + 4;
            j++;
        }
        else if ((str[i] == '1') && (j == 1))
        {
            t = t + 2;
            j++;
        }
        else if ((str[i] == '1') && (j == 2))
        {
            t = t + 1;
            j = 0;
            mas[m] = t;
            m++;
            t = 0;
        }
        else 
        {
            if (j == 0 || j == 1)
            j++;
            else if (j == 2)
            {
                j = 0;
                mas[m] = t;
                m++;
                t = 0;
            }
        }
    }
    return num = mas[0] * 100 + mas[1] * 10 + mas[2];
}
//функция стат, цифровое, буквенное, битовое представление маски прав доступа
int stat_func(char *file, char *number)
{
    int ret;
    struct stat buf;
    if (file[strlen(file) - 1] == '\n')
        file[strlen(file) - 1] = 0;

    if ((ret = stat(file, &buf)) != 0)
    {
        printf("\n\tОшибка ввода файла");
        return 0;
    }
    char tmp[9] = {};
    int i = 0;
    if (S_IRUSR & buf.st_mode)
    {
        number[i] = '1';
        tmp[i] = 'r';
        i++;
    }     
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }
    if (S_IWUSR & buf.st_mode) 
    {
        number[i] = '1';
        tmp[i] = 'w';
        i++;
    }
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }
    if (S_IXUSR & buf.st_mode)
    {
        number[i] = '1';
        tmp[i] = 'x';
        i++;
    }    
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }
    if (S_IRGRP & buf.st_mode) 
    {
        number[i] = '1';
        tmp[i] = 'r';
        i++;
    }
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }
    if (S_IWGRP & buf.st_mode) 
    {
        number[i] = '1';
        tmp[i] = 'w';
        i++;
    }
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }
    if (S_IXGRP & buf.st_mode) 
    {
        number[i] = '1';
        tmp[i] = 'x';
        i++;
    }
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }
    if (S_IROTH & buf.st_mode) 
    {
        number[i] = '1';
        tmp[i] = 'r';
        i++;
    }
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }
    if (S_IWOTH & buf.st_mode) 
    {
        number[i] = '1';
        tmp[i] = 'w';
        i++;
    }
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }
    if (S_IXOTH & buf.st_mode)
    {
        number[i] = '1';
        tmp[i] = 'x';
        i++;
    }
    else 
    {
        number[i] = '0';
        tmp[i] = '-';
        i++;
    }

    if (file[strlen(number) - 1] == '\n')
        file[strlen(number) - 1] = 0;
    if (file[strlen(tmp) - 1] == '\n')
        file[strlen(tmp) - 1] = 0;
    printf("\n\tБитовое представление прав доступа: %s", number);
    printf("\n\tБуквенное представление прав доступа: %s", tmp);
    i = binary_to_number(number);
    printf("\n\tЦифровое представление прав доступа: %d", i);
}