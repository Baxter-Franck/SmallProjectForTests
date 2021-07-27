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

#define SYSCTL_PERIPH_I2C_USED  SYSCTL_PERIPH_I2C1
#define I2C_USED                I2C1_BASE

void InitI2C1(void);
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);
void I2CSendString(uint32_t slave_addr, char array[]);
//read specified register on slave device
uint32_t I2CReceive(uint32_t slave_addr, uint8_t reg);

#endif // __DDII2CFRANCK_H__
