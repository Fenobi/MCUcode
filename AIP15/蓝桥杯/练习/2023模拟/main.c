#include "smg.h"
#include "led.h"
#include "key.h"
#include "iic.h"
#include "public.h"

u8 key_val, key_down, key_down, key_up, key_old;
u8 key_slow_down;
u8 smg_num_display[] = {10, 10, 10, 10, 10, 10, 10, 10};
u8 smg_point_display[] = {0, 0, 0, 0, 0, 0, 0, 0};
u8 smg_slow_down;
u8 led_addr_display[] = {0, 0, 0, 0, 0, 0, 0, 0};
u8 pos;

u8 mode;
u8 vol;
u8 dB;

void key()
{
    if(key_slow_down)
        return;
    key_slow_down = 0;
    key_val = key_value();
    key_down = key_val & (key_val ^ key_old);
    key_up = ~key_val & (key_val ^ key_old);
    key_old = key_val;


}

void smg()
{
    if(smg_slow_down)
        return;
    smg_slow_down = 1;
   
}

void led()
{

}

void Timer0_Isr(void) interrupt 1
{
	vol = AD_read(0x43);
    smg_num_display[0] = vol / 100;
    smg_num_display[1] = vol / 10 % 10;
    smg_num_display[2] = vol % 10;
    if(smg_slow_down==500)
        smg_slow_down = 0;
    if(key_slow_down==10)
        key_slow_down = 0;
    if(++pos==8)
        pos = 0;
    smg_display(pos, smg_num_display[pos], smg_point_display[pos]);
    led_display(pos, led_addr_display[pos]);
}

void Timer0_Init(void) // 1毫秒@12.000MHz
{
    AUXR &= 0x7F; // 定时器时钟12T模式
    TMOD &= 0xF0; // 设置定时器模式
    TL0 = 0x18;   // 设置定时初始值
    TH0 = 0xFC;   // 设置定时初始值
    TF0 = 0;      // 清除TF0标志
    TR0 = 1;      // 定时器0开始计时
    ET0 = 1;      // 使能定时器0中断
    EA = 1;
}

void main()
{
    Timer0_Init();
    pos = 0;
    while (1)
    {
        key();
        smg();
        led();
    }
}