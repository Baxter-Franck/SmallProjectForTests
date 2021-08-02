/**
* Module Name: ddi_eep_i2c.h
*
* Copyright 2011 Hill-Rom
* All Rights Reserved.
*
* The information contained herein is confidential
* property of Hill-Rom. The user, copying, transfer or
* disclosure of such information is prohibited except
* by express written agreement with Hill-Rom.
*
* Module Description:
* -------------------
* This file is a driver interface for i2c.
* In this case used for I2C of OIML Scale function merge in ICB
*    Author: Franck FURIC
*    Date: 2021-07-29 15:24 French Time
*    Revision: 1
*    Source: ddi_scale_i2c
*/

#ifndef __DDI_SCALE_I2C_H__
#define __DDI_SCALE_I2C_H__

#include "defines_HR.h" // Only for HR_Sys_Clock_Freq
#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_i2c.h"
#include "hw_ints.h"
#include "gpio.h"
#include "pin_map.h"
#include "i2c.h"
#include "rom_map.h"
#include "interrupt.h"

// Alias for Periph and gpio for eeprom Merge Scale OIML
#define SCALE_I2C_PERIPH_I2C         SYSCTL_PERIPH_I2C1
#define SCALE_I2C_PERIPH_GPIO        SYSCTL_PERIPH_GPIOG
#define SCALE_I2C_MASTER         I2C1_BASE

#define SCALE_I2C_GPIO_ALT_I2C1_SCL  GPIO_PG0_I2C1SCL
#define SCALE_I2C_GPIO_ALT_I2C1_SDA  GPIO_PG1_I2C1SDA

#define SCALE_I2C_GPIO_PORT          GPIO_PORTG_BASE
#define SCALE_I2C_PIN_SCL            GPIO_PIN_0
#define SCALE_I2C_PIN_SDA            GPIO_PIN_1

#define SCALE_I2C_INT                INT_I2C1

#define DDI_I2C_MAXRETRY  0x7000

// The states in the interrupt handler state machine.
typedef enum{
    STATE_IDLE,
    STATE_WRITE_NEXT,
    STATE_WRITE_FINAL,
    STATE_WAIT_ACK,
    STATE_SEND_ACK,
    STATE_READ_ONE,
    STATE_READ_FIRST,
    STATE_READ_NEXT,
    STATE_READ_FINAL,
    STATE_READ_WAIT
}STATE_INT_I2C;

void DdiScaleI2cInit(void);
void DdiScaleI2cIntHandler(void);
uint8_t DdiScaleI2cWrite1Byte(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t ucData);
uint8_t DdiScaleI2cWrite(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData, uint32_t ulCount);
uint8_t DdiScaleI2cRead1Byte(uint8_t ucSlv_Addr, uint8_t ucRegister);
uint8_t DdiScaleI2cRead(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData, uint32_t ulCount);
BOOLEAN DdiScaleI2cWriteVerify(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData,uint32_t ulCount);

#endif // __DDI_SCALE_I2C_H__
