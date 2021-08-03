#include "ioExp.h"

void configIO1(void)
{	
    DdiScaleI2cWrite1Byte(IOEXP_ADDR, 0xFF, CONF_PORT0);
DdiScaleI2cWrite1Byte(IOEXP_ADDR, 0x00, CONF_PORT1);
DdiScaleI2cWrite1Byte(IOEXP_ADDR, 0xFF, PORT1_OUT);
}
