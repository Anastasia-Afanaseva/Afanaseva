#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include "funk.h"

extern int cnt;
void min_max(num_t *data, int num_1, int num_2)
{
    int min, max, j = 0;
    for (int j = 0; j < num_1; j++)
    {
        min = data->mas[0];
        max = data->mas[0];
        for (int t = 0; t < num_2; t++)
        {
            if (data->mas[t] > max)
            {
                max = data->mas[t];
            }
            if (data->mas[t] < min)
            {
                min = data->mas[t];
            }
        }
        data->max_min[0] = max;
        data->max_min[1] = min;
        data = data + sizeof(num_t);
    }
    return;
}
void func_end(void)
{
    printf("\nSuccess\n");
}

void handler(int val)
{
    printf("\nКоличество обработанных данных: %d\n", cnt);
    signal(SIGINT,SIG_DFL);
    exit(0);
}

void print_num(num_t *data, int num_1, int num_2)
{
    int m;
    for (int i = 0; i < num_1; i++)
    {
        m = 0;
        for (int j = 0; j < num_2; j++)
        {
            data->mas[j] = (1 + rand()%1000);
            m++;
        }
        printf("\n");
        data->size = m;
        data = data + sizeof(num_t);
    }
}