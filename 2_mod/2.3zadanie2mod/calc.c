#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void read(float *x, float *y)
{
    printf("\tВведите первое число:");
    scanf("%f", x);
    printf("\tВведите второе число:");
    scanf("%f", y);
    return;
}

float summ (float x, float y)
{ 
    return x + y;
}

float substr (float x, float y)
{
    return x - y;
}

float multipli (float x, float y)
{
    return x * y;
}

float division (float x, float y)
{   
    if (y != 0)
        return x / y;
    else 
    {
        printf("\tНа 0 делить нельзя\n");
        return 0;
    }
}

float step(float x, float y)
{
    return pow(x,y);
}

float ostatoc (float x, float y)
{
    return (int)x % (int) y;
}

float (*sel(int choice)) (float, float) 
{
    switch (choice) {
        case 1: return summ;
        case 2: return substr;
        case 3: return multipli;
        case 4: return division;
        case 5: return step;
        case 6: return ostatoc;
    }
}
