#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "funk.h"

int main()
{
    int N;
    int cnt = 0;
    int cnt_1 = 0;
    char str_gate[20] = {};
    char str_mask[20] = {};
    uint8_t gate[4] = {0};
    uint8_t mask[4] = {0};
    printf("\nВведите шлюз:");
    fgets(str_gate, 20, stdin);
    printf("\nВведите маску:");
    fgets(str_mask, 20, stdin);
    printf("\nВведите количество пакетов:");
    scanf("%d", &N);
    uint8_t addr[4] = {0};

    if (check_point_number(str_gate) == 0) 
    {
        printf("\nВведено неверное значение узла шлюза");
        return 0;
    }
    
    if (transform(str_gate, gate) ==  0)
    {
        printf("\nВведено неверное значение узла шлюза");
        return 0;
    }

    if (check_point_number(str_mask) == 0) 
    {
        printf("\nВведено неверное значение маски");
        return 0;
    }
    
    if (transform(str_mask, mask) ==  0)
    {
        printf("\nВведено неверное значение маски"); 
        return 0;
    }

    for (int j = 0; j < N; j++) 
    {
        for (int i = 0; i < sizeof(gate); i++)
        {

        addr[i] =  -1 + rand()%256;
        if (gate[i] == (addr[i] & mask[i]))
            cnt_1++;
        }
        if (cnt_1 == 4)
            cnt++;
    }

    printf("\nКоличество пакетов, предназначавшихся узлам своей сети в штуках/процентах:");
    printf("%d / %f %%\n", cnt, ((float)cnt / N) * 100);
    printf("Количество пакетов, предназначавшихся узлам других сетей в штуках/процентах:");
    printf("%d / %f %%\n", N - cnt, ((float)(N - cnt) / N) * 100);
    return 0;
}