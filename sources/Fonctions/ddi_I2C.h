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

typedef enum {
    I2C_NO_ERROR = 0,
    I2C_ERROR_TIMEOUT_1 = 1,
    I2C_ERROR_TIMEOUT_2 = 2,
    I2C_ERROR_TIMEOUT_3 = 3,
    I2C_ERROR_TIMEOUT_4 = 4,
    I2C_ERROR_TIMEOUT_5 = 5,
    I2C_ERROR_TIMEOUT_6 = 6,
    I2C_ERROR_TIMEOUT_7 = 7,
    I2C_ERROR_TIMEOUT_8 = 8,
    I2C_ERROR_TIMEOUT_9 = 9,
    I2C_ERROR_MASTER = 10
}I2C_error;

void init_i2c(void);
uint8_t i2c_Write(uint8_t slave_addr, uint16_t  valToSend, uint8_t reg);
uint8_t i2c_Read(uint32_t * PData, uint32_t slave_addr, uint8_t reg);

#endif // __DDII2C_H__
