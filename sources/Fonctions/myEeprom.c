#include "myEeprom.h"


void configEEPREOM(void)
{	

}

uint8_t myEepromWrite(uint8_t address, uint8_t data)
{
    return i2c_Write(ADDR_EEPROM_BLOCK_0, data, address);
}

uint8_t myEepromRead(uint8_t address)
{
    uint32_t rx=0;
    i2c_Read(&rx, ADDR_EEPROM_BLOCK_0, address);
    return (uint8_t)rx;
}

