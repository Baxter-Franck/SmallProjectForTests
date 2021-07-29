#ifndef __MY_FUNCTIONS_H__
#define __MY_FUNCTIONS_H__

#include "ioExp.h"
#include "ioExp2.h"
#include "watchdog_ext.h"
#include "interrupt.h"
#include "hw_ints.h"
#include "myEeprom.h"
#include <string.h> // for memset
#include "uart.h"
#include "uartstdio.h"
#include "stdlib.h"
#include "stdint.h"
#include "debug.h" // for ASSERT
#include "ddi_I2C_franck.h"
#include "ddi_scale_eeprom_i2c.h"

typedef enum{
    NO_BUTTON = 	0x00,
    PLUS_PRESSED = 	0x10,
    CAL_PRESSED = 	0x20,
    MINUS_PRESSED = 0x40
} BUTTON_TYPE;

void exampleChenillard(int);
void exampleButtonPress(void);
void exempleButtonPressInt(void);
void exempleIO2Chenillard(uint8_t type, uint32_t delay);
void exempleIO2ChenilladWithDriverFranck(void);
void exempleEEPROMDriverFrancknotinWhileLOOP(void);
void exempleDDI_EEPROM_INTERRUP_notinWhileLOOP(void);
void exempleEEPROMnotinWhileLOOP(void);

void setGreenLed(bool v);
void setYellowLed(bool v);
void setRedLed(bool v);
void setLed(uint8_t v);
BUTTON_TYPE checkButtonPress(void);
uint8_t checkButtonPressInt(void);
void configInterrupt(void);
void initUART0(void); //=> l'écriture ne fonctionne pas pour le moment


void sleep_ms(uint32_t time);
void sleep_s(uint32_t time);
void testVariableParameter(uint8_t num_of_args, ...);

#endif // __MY_FUNCTIONS_H__
