#ifndef __IOEXP_H__
#define __IOEXP_H__

#include "ddi_scale_i2c.h"
#include "string.h"
#include "myFunctions.h"

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

void configIO1(void);

#endif // __IOEXP_H__
