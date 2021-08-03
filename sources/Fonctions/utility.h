#ifndef __UTILITY_H__
#define __UTILITY_H__

#include "defines_HR.h" // Only for HR_Sys_Clock_Freq
#include <sysctl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <hw_memmap.h>
#include <hw_types.h>
#include <hw_i2c.h>
#include <hw_ints.h>
#include <gpio.h>
#include <pin_map.h>
#include <i2c.h>
#include <rom_map.h>
#include <interrupt.h>
#include <debug.h> // for ASSERT

#include "ddi_uart.h"


// ENABLE TRACE FOR DEBUG ONLY
#define LOG(...) uartPrintln(__VA_ARGS__)
#define LOGNL(...) uartPrint(__VA_ARGS__)
#define CLEAR_LOG uartPrint("\33\143");

//! - \%c to print a character
//! - \%d or \%i to print a decimal value
//! - \%s to print a string
//! - \%u to print an unsigned decimal value
//! - \%x to print a hexadecimal value using lower case letters
//! - \%X to print a hexadecimal value using lower case letters (not upper case
//! letters as would typically be used)
//! - \%p to print a pointer as a hexadecimal value
void uartPrint(const char *pcString, ...);
void uartPrintln(const char *pcString, ...);

#endif // __UTILITY_H__
