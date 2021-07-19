#include "myFunctions.h"


extern int cpt,taille;
extern uint8_t value;

uint32_t rxByte;

BUTTON_TYPE checkButtonPress(void)
{
    BUTTON_TYPE ret = NO_BUTTON;
    if(Ddi_i2c_ReadI2C_IOEXP(&rxByte, IOEXP_ADDR, PORT0_IN))
    {
        ret = (BUTTON_TYPE)((~rxByte & 0x70) & 0xFF);
    }
    return ret;
}

void setGreenLed(bool v){
	
	value = (v)?0xBF:0xFF;
	Ddi_i2c_SendI2C_IOEXP(IOEXP_ADDR, value, PORT1_OUT);
}

void setRedLed(bool v){
    value = (v)?0xDF:0xFF;
        Ddi_i2c_SendI2C_IOEXP(IOEXP_ADDR, value, PORT1_OUT);
}

void setYellowLed(bool v){
    value = (v)?0xEF:0xFF;
        Ddi_i2c_SendI2C_IOEXP(IOEXP_ADDR, value, PORT1_OUT);
}

void setLed(uint8_t v){
    Ddi_i2c_SendI2C_IOEXP(IOEXP_ADDR, v, PORT1_OUT);
}


void chenillard(int type)
{
	switch (type)
	{
		case 1:
		{
			cpt=0;
			value = 0xE0;
			while(1)
			{
				sleep_ms(120);
				if(cpt==0)
				{
					value ^= (5<<4);
				}else if(cpt == 1)
				{
					value ^= (6<<4);
				}else if(cpt == 2){
					value ^= (3<<4);
				}else{
					value = 0x8F;
				}
				(cpt>=2)?cpt=0:cpt++;
				
				Ddi_i2c_SendI2C_IOEXP(IOEXP_ADDR, value, PORT1_OUT);
			}
			//break;
		}
		default:
		{
			cpt=0;
			value = 0xEF;
			while(1)
			{
				sleep_ms(500);
				if(cpt==0)
				{
					value ^= (5<<4);
				}else if(cpt == 1)
				{
					value ^= (6<<4);
				}else if(cpt == 2){
					value ^= (3<<4);
				}else{
					value = 0x8F;
				}
				(cpt>=2)?cpt=0:cpt++;
				
				Ddi_i2c_SendI2C_IOEXP(IOEXP_ADDR, value, PORT1_OUT);
			}
			//break;
		}
	}
	
	
}

void sleep_ms(uint32_t time)
{
	// SysCtlDelay(n) performs n loop.
	// For each loop, 3 instructions. Period for each loop = 3* (1/freq osc), 1 CLK per instruction
	// Temporization = 300000*(3*1/80MHz) = 11 ms
	SysCtlDelay(time*80000/3);
}

void sleep_s(uint32_t time)
{
	// SysCtlDelay(n) performs n loop.
	// For each loop, 3 instructions. Period for each loop = 3* (1/freq osc), 1 CLK per instruction
	// Temporization = 300000*(3*1/80MHz) = 11 ms
	SysCtlDelay(time*80*1e6/3);
}

