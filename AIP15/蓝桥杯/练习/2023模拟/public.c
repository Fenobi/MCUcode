#include "public.h"

void Delay1ms() //@12.000MHz
{
    unsigned char i, j;

    i = 12;
    j = 169;
    do
    {
        while (--j)
            ;
    } while (--i);
}

void DelayNms(u16 n)
{
    while(n--)
    {
        Delay1ms();
    }
}