#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int i = 0;
    int summ = 0;
    while(argv[++i] != NULL)
        summ = summ + atoi(argv[i]);
    printf("\nСумма аргументов:%d ",summ);
    printf("\n");
    return 0;
}