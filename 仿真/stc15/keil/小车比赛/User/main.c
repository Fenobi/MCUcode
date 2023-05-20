#include <STC15F2K60S2.H>
#include "IIC_LCD12864.h"

void main()
{
    while(1)
    {
        Ds1302Init();
        DS1302_month();
    }
}