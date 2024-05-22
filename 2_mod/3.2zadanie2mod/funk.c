#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "funk.h"

int check_point_number(char *str_gate)
{
//зануляем последний символ если он равен пропуску строки
    int size = strlen(str_gate);
     if (str_gate[size - 1] == '\n')
    {
        str_gate[size - 1] = '\0';
        size = size - 1;
    }
    // проверка состоит ли стрка из точек и чисел
    for (int i = 0; i < size; i++)
    {
        if ((str_gate[i] >= '0') && (str_gate[i] <= '9') ||
         (str_gate[i] == '.') || (str_gate[i] == '\0'))
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

int transform(char *str_gate, uint8_t *gate)
{
    int i = 0, j =0, m = 0, cnt_pnt = 0;
    char str_gate_n[5] = {};
    //перевод строки шлюза в массив чисел
     int size = strlen(str_gate);
    while (i != (size + 1))
    {
        if ((str_gate[i] != '.') && (str_gate[i] != '\0'))
        {
            str_gate_n[j] = str_gate[i];
            i++;
            j++;
        }
        else
        {
            cnt_pnt++;
            if ((strlen(str_gate_n) != 0) && (atoi(str_gate_n) >= 0) && (atoi(str_gate_n) <= 255))
            {
                gate[m] = atoi(str_gate_n);
                m++;
                i++;
                memset(str_gate_n, 0, 5);
                j = 0;
                if (cnt_pnt != m)
                    return 0;
            }
            else
                return 0;
        }
    }
    if (m == 4) 
        return 1;
    else 
        return 0;
}