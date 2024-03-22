#include <stdio.h>
#include <stdlib.h>

void read(float *x, float *y)
{
    printf("\tВведите первое число:");
    scanf("%f", x);
    printf("\tВведите второе число:");
    scanf("%f", y);
    return;
}

void summ (float x, float y)
{ 
    printf("\t%f\n", x + y);
}

void substr (float x, float y)
{
    printf("\t%f\n", x - y);
}

void multipli (float x, float y)
{
    printf("\t%f\n", x * y);
}

void division (float x, float y)
{   
    if (y != 0.0 || y != 0)
        printf("\t%f\n", x / y);
    else printf("\tНа 0 делить нельзя\n");
}

void exit_calc (void)
{
    exit(0);
}

