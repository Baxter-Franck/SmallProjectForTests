#ifndef __DDII2C_H__
#define __DDII2C_H__

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

void init_i2c(void);
uint8_t i2c_Write(uint8_t slave_addr, uint16_t  valToSend, uint8_t reg);
uint8_t i2c_Read(uint32_t * PData, uint32_t slave_addr, uint8_t reg);

#endif // __DDII2C_H__
