#include "public.h"

sbit SCK=P1^7;
sbit RST=P1^3;
sbit SDA=P2^3;

void set_time_func(u8* arr);
void read_time_func(u8* arr);