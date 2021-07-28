#include "ioExp2.h"

TCA9535_t tca9535;

void configIO2(void)
{	
	//tca9535.PolarityInversion.all = 0;

    tca9535.Config.ports.P0.all = 0x00;  // Port 0 as output
    tca9535.Config.ports.P1.all = 0x00;  // Port 1 as output
    tca9535.Output.all = 0x0000;

    i2c_Write(IOEXP2_ADDR, tca9535.Config.all, TCA9535_CONFIG_REG0);
    //i2c_Write(IOEXP2_ADDR, tca9535.PolarityInversion.all, TCA9535_POLARITY_REG0);
    i2c_Write(IOEXP2_ADDR, tca9535.Output.all, TCA9535_OUTPUT_REG0);
}

void updateIO2()
{
    i2c_Write(IOEXP2_ADDR, tca9535.Output.all, TCA9535_OUTPUT_REG0);
}
