#include "myEeprom.h"


void configEEPREOM(void)
{	

}

void myEepromWrite(uint8_t address, uint8_t data)
{
    i2c_Write(ADDR_EEPROM_BLOCK0, data, address);
}

uint8_t myEepromRead(uint8_t address)
{
    uint32_t rx=0;
    i2c_Read(&rx, ADDR_EEPROM_BLOCK0, address);
    return (uint8_t)rx;
}

