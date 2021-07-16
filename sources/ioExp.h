#ifndef __IOEXP_H__
#define __IOEXP_H__

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

#define IOEXP_ADDR 0x24

// Regiter Address
#define PORT0_IN	0x00
#define PORT1_OUT	0x03
#define CONF_PORT0 	0x06
#define CONF_PORT1 	0x07

static const uint8_t NB_ERR_OCC = 30;

typedef struct {
	uint8_t id;
	uint8_t Port_P0;
	uint8_t Port_P1;
} IOExpender_t;

void Ddi_ioexp_Init(void);
void Ddi_ioexpS_Init(IOExpender_t io);
uint8_t Ddi_i2c_SendI2C_IOEXP(uint8_t slave_addr, uint16_t  valToSend, uint8_t reg);


#endif // __IOEXP_H__
