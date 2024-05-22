#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>



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
    if (y != 0)
        printf("\t%f\n", x / y);
    else printf("\tНа 0 делить нельзя\n");
}

void step (float x, float y)
{
    printf("\t%f\n", pow(x,y));
}

void ostatoc (float x, float y)
{
     printf("\t%d\n",(int)x % (int)y);
}

void exit_calc (void)
{
    exit(0);
}

