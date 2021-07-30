#include "ioExp.h"

const uint8_t sizeArray=10;
uint8_t array_i2c[sizeArray];
uint8_t array1_i2c[sizeArray];
	
void configIO1(void)
{	
    i2c_Write(IOEXP_ADDR, 0xFF, CONF_PORT0);
    i2c_Write(IOEXP_ADDR, 0x00, CONF_PORT1);
    i2c_Write(IOEXP_ADDR, 0xFF, PORT1_OUT);	
}

void ReadWrite_i2cEepromOutOfLoop(void)
{
    
    uint8_t i=0;
    uint32_t data=0;

    memset(array_i2c, 42, sizeof(array_i2c)); // init array at 0
    memset(array1_i2c, 43, sizeof(array1_i2c)); // init array at 0

    // ecriture en eeprom BLOCK_0
    for(i=0; i<sizeArray ;i++)
    {
        array_i2c[i] =i2c_Write(0x50, 1+i, i);
        //sleep_ms(5);
    }

    i=0;

    // ecriture en eeprom BLOCK_1
    for(i=0; i<sizeArray ;i++)
    {
        array1_i2c[i] =i2c_Write(0x51, 20+i, i);
        //sleep_ms(5);
    }

    i=0;
    // lecture de l'eeprom BLOCK_0 et mise dans le tableau arry
    for(i=0; i<sizeArray ;i++)
    {
        data=0;
        array_i2c[i] = i2c_Read(&data, 0x50, i);
        array_i2c[i] = data;
		//sleep_ms(5);
    }

    i=0;

    // lecture de l'eeprom BLOCK_1 et mise dans le tableau arry
    for(i=0; i<sizeArray ;i++)
    {
        data=0;
        array1_i2c[i] = i2c_Read(&data, 0x51, i);
        array1_i2c[i] = data;
		//sleep_ms(5);
    }
    i=0;
}
