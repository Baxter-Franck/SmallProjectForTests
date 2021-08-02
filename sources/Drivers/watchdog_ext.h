#ifndef __WATCHDOG_EXT_H__
#define __WATCHDOG_EXT_H__

#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "gpio.h"

void Ddi_watchdog_init(void);
void Ddi_watchdog_set(void);
void Ddi_watchdog_reset(void);

#endif //__WATCHDOG_EXT_H__
