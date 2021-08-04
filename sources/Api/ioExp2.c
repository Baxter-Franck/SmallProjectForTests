#include "ioExp2.h"

TCA9535_t IOExp2;

void configIOExp2(void)
{	
	//tca9535.PolarityInversion.all = 0;

    IOExp2.PolarityInversion.all = 0x0000;
    IOExp2.Config.all = 0x0000;
    IOExp2.Output.all = 0x0000;

    ioExp2Write(TCA9535_CONFIG_REG0, IOExp2.Config.all);
    ioExp2Write(TCA9535_POLARITY_REG0, IOExp2.PolarityInversion.all);
    ioExp2Write(TCA9535_OUTPUT_REG0, IOExp2.Output.all);
}

uint8_t ioExp2Write(uint8_t address, uint16_t data)
{
    uint8_t convData[2];
    convData[0] = (data & 0x00FF) ;
    convData[1] = (data >> 8);
    return DdiScaleI2cWrite(IOEXP2_ADDR, address, convData, sizeof(convData));
}

void updateIO2()
{
    ioExp2Write(TCA9535_OUTPUT_REG0, IOExp2.Output.all);
}
