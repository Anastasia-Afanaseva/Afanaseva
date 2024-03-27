#include <stdio.h>
#include "calc.h"


int main ()
{   
    int opt;

    float x, y;
    while (1)
    {   
        printf("\tВыберите функцию:\n\t1 - Сложение");
        printf("\t2 - Вычитание");
        printf("\t3 - Умножение");
        printf("\t4 - Деление");
        printf("\t5 - Возведение в степень");
        printf("\t6 - Остаток от деления");
        printf("\t7 - Выключить калькулятор\n");
        scanf("%d", &opt);
       
        switch(opt)
        {
            case 1:
            {
                read(&x, &y);
                summ(x, y);
                break;
            }
            case 2:
            {
                read(&x, &y);
                substr(x, y);
                break;
            }
            case 3:
            {
                read(&x, &y);
                multipli(x,y);
                break;
            }
            case 4:
            {
                read(&x, &y);
                division(x, y);
                break;
            }
            case 5:
            {
                read(&x, &y);
                step(x, y);
                break;
            }
            case 6:
            {
                read(&x,&y);
                ostatoc(x,y);
                break;
            }
            case 7:
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
    return 0;
}