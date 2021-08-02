#include "ioExp2.h"

TCA9535_t tca9535;

void configIO2(void)
{	
	//tca9535.PolarityInversion.all = 0;

    tca9535.PolarityInversion.all = 0x0000;
    tca9535.Config.all = 0x0000;
    tca9535.Output.all = 0x0000;

    DdiScaleI2cWrite1Byte(IOEXP2_ADDR, TCA9535_CONFIG_REG0, tca9535.Config.all);
    //DdiScaleI2cWrite1Byte(IOEXP2_ADDR, TCA9535_POLARITY_REG0, tca9535.PolarityInversion.all);
    DdiScaleI2cWrite1Byte(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, tca9535.Output.all);
}

void updateIO2()
{
    DdiScaleI2cWrite1Byte(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, tca9535.Output.all);
}
