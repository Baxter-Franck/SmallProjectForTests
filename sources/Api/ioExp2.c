#include "ioExp2.h"

IOExp2_Data_t IOExp2;

void configIOExp2(void)
{	
	DdiScaleI2cWrite2Bytes(ADDR_IO_EXP_2, TCA9535_CONFIG_REG0, 0x00); // INT_ACCELERO is input
    ioExp2Write(TCA9535_OUTPUT_REG0, IOExp2);
}

uint8_t ioExp2Write(uint8_t address, IOExp2_Data_t data)
{
    return DdiScaleI2cWrite2Bytes(ADDR_IO_EXP_2, address, data.all);
}

void updateIO2()
{
    ioExp2Write(TCA9535_OUTPUT_REG0, IOExp2);
}
