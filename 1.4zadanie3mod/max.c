#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int i = 1;
    int max = atoi(argv[1]);
    while(argv[++i] != NULL)
        if (atoi(argv[i]) > max)
            max = atoi(argv[i]);
    printf("\nНаибольшее значение:%d ",max);
    printf("\n");
    return 0;
}