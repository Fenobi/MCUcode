#include "ds18b20.h"
#include "smg.h"

void main()
{
	ds18b20_init();
	
	while(1)
	{	
		Display_2_2Wei_XS(1,ds18b20_read_temperture());
	}
}
