#include <REGX52.H>

typedef unsigned char u8;
typedef unsigned int u16;

sbit LSA = P1^0;
sbit LSB = P1^1;
sbit LSC = P1^2;

extern u8 gamg_code[17];

#define SMG_A_DP_PORT P0

void smg_display();