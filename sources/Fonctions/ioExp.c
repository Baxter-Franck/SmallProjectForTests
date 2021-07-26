#include "ioExp.h"

void configIO1(void)
{	
	i2c_Write(IOEXP_ADDR, 0xFF, CONF_PORT0);
    i2c_Write(IOEXP_ADDR, 0x00, CONF_PORT1);
    i2c_Write(IOEXP_ADDR, 0xFF, PORT1_OUT);	
}
