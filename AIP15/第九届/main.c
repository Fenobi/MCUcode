#include "smg.h"
#include "ds18b20.h"

void main()
{
	ds18b20_init();
	while(1)
	{
		Display_2_2Wei_XS(1,12.21);
	}
}