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
* In this case used for EEPROM of OIML Scale function merge in ICB
*    Author: Franck FURIC
*    Date: 2021-07-29 15:24 French Time
*    Revision: 1
*    Source: ddi_scale_eeprom_i2c
*/

#ifndef __DDI_SCALE_EEPROM_I2C_H__
#define __DDI_SCALE_EEPROM_I2C_H__

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
#define SCALE_EEPROM_PERIPH_I2C         SYSCTL_PERIPH_I2C1
#define SCALE_EEPROM_PERIPH_GPIO        SYSCTL_PERIPH_GPIOG
#define SCALE_EEPROM_I2C_MASTER         I2C1_BASE

#define SCALE_EEPROM_GPIO_ALT_I2C1_SCL  GPIO_PG0_I2C1SCL
#define SCALE_EEPROM_GPIO_ALT_I2C1_SDA  GPIO_PG1_I2C1SDA

#define SCALE_EEPROM_GPIO_PORT          GPIO_PORTG_BASE
#define SCALE_EEPROM_PIN_SCL            GPIO_PIN_0
#define SCALE_EEPROM_PIN_SDA            GPIO_PIN_1

#define SCALE_EEPROM_INT                INT_I2C1

// Address for 24LC16B
#define BLOCK_0_EEPROM      0x50
#define BLOCK_1_EEPROM      0x51

#define DDI_EEPROM_MAXRETRY  0x7000

//Interrupt priority ==> move in other file
#define INTERRUPT_1ST_PRIORITY    0x0 //ADS1241 Loadbeam data interrupt
#define INTERRUPT_2ND_PRIORITY    0x1 //EEPROM
#define INTERRUPT_3RD_PRIORITY    0x2
#define INTERRUPT_4TH_PRIORITY    0x3
#define INTERRUPT_5TH_PRIORITY    0x4
#define INTERRUPT_6TH_PRIORITY    0x5
#define INTERRUPT_LST_PRIORITY    0x6

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
}STATE_INT_EEPROM;

void DdiScaleEepromI2cInit(void);
void DdiScaleEepromI2cIntHandler(void);
uint8_t DdiScaleEepromI2cWrite(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData, uint32_t ulCount);
uint8_t DdiScaleEepromI2cRead(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData, uint32_t ulCount);
//BOOLEAN DdiEepI2cWriteVerify(UNSIGNED8 ucSlv_Addr, UNSIGNED8 *pucData, UNSIGNED32 ulOffset,UNSIGNED32 ulCount);

/* // save
extern void DdiEepI2cInit(void);
extern void DdiEepI2cIntHandler(void);
extern void DdiEepI2cRead(UNSIGNED8 ucSlv_Addr, UNSIGNED8 *pucData, UNSIGNED32 ulOffset, UNSIGNED32 ulCount);
extern void DdiEepI2cWrite(UNSIGNED8 ucSlv_Addr, UNSIGNED8 *pucData, UNSIGNED32 ulOffset, UNSIGNED32 ulCount);
extern BOOLEAN DdiEepI2cWriteVerify(UNSIGNED8 ucSlv_Addr, UNSIGNED8 *pucData, UNSIGNED32 ulOffset,UNSIGNED32 ulCount);
*/

#endif // __DDI_SCALE_EEPROM_I2C_H__
