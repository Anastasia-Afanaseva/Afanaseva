#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "choice.h"
#include "ostat.h"
#include "step.h"
#include "divis.h"
#include "summ.h"
#include "subst.h"
#include "multi.h"

int main ()
{   
    float (*operation)(float, float);
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
        if (opt == 7) 
            exit(0);
        else if ((opt < 1) || (opt > 7))
        {
            printf("\tВведена некорректная функция\n");   
            continue;
        }

        operation = sel(opt);
        read(&x, &y);
        float result = operation(x, y);
        printf("\tРезультат: %f \n", result);
        
    }
    return 0;
}
    