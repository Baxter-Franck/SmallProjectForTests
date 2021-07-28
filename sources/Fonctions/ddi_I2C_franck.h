#ifndef __DDII2CFRANCK_H__
#define __DDII2CFRANCK_H__

#include "defines_HR.h" // Only for HR_Sys_Clock_Freq
#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"
#include "pin_map.h"
#include "i2c.h"
#include "hw_types.h"
#include "hw_i2c.h"
#include "stdarg.h" // use for va_arg va_start va_end
#include "ddi_I2C.h"

#define SYSCTL_PERIPH_I2C_USED  SYSCTL_PERIPH_I2C1
#define I2C_USED                I2C1_BASE

#define EEPROM_BLOCK_0 0x50
#define EEPROM_BLOCK_1 0x51

void InitI2C1_Franck(void);
uint8_t I2CSendFranck(uint8_t slave_addr, uint8_t CMD, uint8_t nbOctetsSend, ...);
uint8_t I2CSendOneByteFranck(uint8_t slave_addr, uint8_t CMD, uint8_t value);
uint32_t I2CReceiveOneByteFranck(uint32_t slave_addr, uint8_t CMD);
//todo: faire un multiple bytes

#endif // __DDII2CFRANCK_H__
