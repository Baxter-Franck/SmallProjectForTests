#ifndef __MY_FUNCTIONS_H__
#define __MY_FUNCTIONS_H__

#include "ioExp.h"
#include "watchdog_ext.h"

typedef enum{
    NO_BUTTON = 	0x00,
    PLUS_PRESSED = 	0x10,
    CAL_PRESSED = 	0x20,
    MINUS_PRESSED = 0x40
} BUTTON_TYPE;

void sleep_ms(uint32_t time);
void sleep_s(uint32_t time);
void chenillard(int);
void setGreenLed(bool v);
void setYellowLed(bool v);
void setRedLed(bool v);
void setLed(uint8_t v);
BUTTON_TYPE checkButtonPress(void); //P04

#endif // __MY_FUNCTIONS_H__
