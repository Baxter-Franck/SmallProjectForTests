#include <ExEeprom.h>
#include "debug.h"

uint8_t ExEepromWrite(uint8_t block, uint8_t address, uint8_t data)
{
    ASSERT(block<=7);
    ASSERT(address<=255);

    return DdiScaleI2cWrite1Byte(block, address, data);
}

uint8_t ExEepromRead(uint8_t block, uint8_t address)
{
    ASSERT(block<=7);
    ASSERT(address<=255);
    return DdiScaleI2cRead1Byte(block, address);
}

