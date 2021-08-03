#ifndef __MYEEPROM_H__
#define __MYEEPROM_H__

#include "ddi_scale_i2c.h"
#include "utility.h"

// Address for EEPROM 24LC16B
// 0 1 0 1 | 0 B2 B1 B0 
// 0x50 ==> 0x57
#define ADDR_EEPROM 0x50
#define ADDR_EEPROM_BLOCK_0 0x50
#define ADDR_EEPROM_BLOCK_1 0x51
#define ADDR_EEPROM_BLOCK_2 0x52
#define ADDR_EEPROM_BLOCK_3 0x53
#define ADDR_EEPROM_BLOCK_4 0x54
#define ADDR_EEPROM_BLOCK_5 0x55
#define ADDR_EEPROM_BLOCK_6 0x56
#define ADDR_EEPROM_BLOCK_7 0x57


void ExEEPROM_Init(void);
void ExEEPROM_Write(uint8_t block, uint8_t address, uint8_t length, void* pointer);
void ExEEPROM_WriteCritic(uint8_t block, uint8_t address, uint8_t length, void* pointer);
uint8_t ExEEPROM_Read(uint8_t block, uint8_t address, uint8_t length, void* pointer);
uint8_t ExEEPROM_ReadCritic(uint8_t block, uint8_t address, uint8_t length, void* pointer)   ;
PRIVATE void ExEEPROMRecover(uint8_t block, uint8_t address, uint8_t length, void *write_pointer, void *read_pointer);


/*void I2CWriteCriticalData(UNSIGNED8 EE_Bank1,UNSIGNED8 ucSub_Addr1,UNSIGNED8 length,void *pointer);
UNSIGNED8 I2CReadCriticalData(UNSIGNED8 EE_Bank1,UNSIGNED8 ucSub_Addr1,UNSIGNED8 length, void *pointer);
UNSIGNED8 I2CReadCriticalDataDiag(UNSIGNED8 EE_Bank1,UNSIGNED8 ucSub_Addr1,UNSIGNED8 length, void *pointer);
void I2CWriteCriticalDataDiag(UNSIGNED8 EE_Bank1,UNSIGNED8 ucSub_Addr1,UNSIGNED8 length,void *pointer);
*/
#endif // __MYEEPROM_H__
