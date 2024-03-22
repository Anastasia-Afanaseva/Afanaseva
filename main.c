#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main ()
{   
    void (*operation)(float x, float y);
    int opt;

    float x, y;
    while (1)
    {   
        printf("\tВыберите функцию:\n\t1 - Сложение");
        printf("\t2 - Вычитание");
        printf("\t3 - Умножение");
        printf("\t4 - Деление");
        printf("\t5 - Выключить калькулятор\n");
        scanf("%d", &opt);
       
        switch(opt)
        {
            case 1:
            {
                read(&x, &y);
                operation = summ;
                operation(x, y);
                break;
            }
            case 2:
            {
                read(&x, &y);
                operation = substr;
                operation(x, y);
                break;
            }
            case 3:
            {
                read(&x, &y);
                operation = multipli;
                operation(x, y);
                break;
            }
            case 4:
            {
                read(&x, &y);
                operation = division;
                operation(x, y);
                break;
            }
            case 5:
            {
                exit_calc();
                break;
            }
            default:
            {
                printf("\tВведена некорректная опция\n");
                break;
            }
        }
    }
}
