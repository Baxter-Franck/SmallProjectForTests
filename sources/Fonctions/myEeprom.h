#ifndef __MYEEPROM_H__
#define __MYEEPROM_H__

#include "ddi_I2C.h"

// 0 1 0 1 | 0 B2 B1 B0 
// 0x50 ==> 0x57
#define ADDR_EEPROM_BLOCK0 0x50
#define ADDR_EEPROM_BLOCK1 0x51
#define ADDR_EEPROM_BLOCK2 0x52
#define ADDR_EEPROM_BLOCK3 0x53
#define ADDR_EEPROM_BLOCK4 0x54
#define ADDR_EEPROM_BLOCK5 0x55
#define ADDR_EEPROM_BLOCK6 0x56
#define ADDR_EEPROM_BLOCK7 0x57

void configEEPREOM(void);
uint8_t myEepromWrite(uint8_t address, uint8_t data);
uint8_t myEepromRead(uint8_t address);

#endif // __MYEEPROM_H__
