#ifndef __MYEEPROM_H__
#define __MYEEPROM_H__

#include "ddi_scale_i2c.h"

// Address for EEPROM 24LC16B
// 0 1 0 1 | 0 B2 B1 B0 
// 0x50 ==> 0x57
#define ADDR_EEPROM_BLOCK_0 0x50
#define ADDR_EEPROM_BLOCK_1 0x51
#define ADDR_EEPROM_BLOCK_2 0x52
#define ADDR_EEPROM_BLOCK_3 0x53
#define ADDR_EEPROM_BLOCK_4 0x54
#define ADDR_EEPROM_BLOCK_5 0x55
#define ADDR_EEPROM_BLOCK_6 0x56
#define ADDR_EEPROM_BLOCK_7 0x57

void configEEPREOM(void);
uint8_t ExEepromWrite(uint8_t block, uint8_t address, uint8_t data);
uint8_t ExEepromRead(uint8_t block, uint8_t address);

#endif // __MYEEPROM_H__
