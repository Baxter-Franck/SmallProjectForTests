#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "ioExp.h"
#include "ioExp2.h"
#include "watchdog_ext.h"
#include "myFunctions.h"
#include "myEeprom.h"
#include <uart.h>
#include <uartstdio.h>


// Définition global of µC speed
uint32_t HR_Sys_Clock_Freq;
int cpt,taille;
uint8_t value;
uint16_t value16;
uint32_t reply=0;
bool b;


// I2C_MASTER_ERR_NONE     0
// I2C_MASTER_ERR_ADDR_ACK 0x00000004
// I2C_MASTER_ERR_DATA_ACK 0x00000008
// I2C_MASTER_ERR_ARB_LOST 0x00000010
// I2C_MASTER_ERR_CLK_TOUT 0x00000080


int main(void)
{
    HR_Sys_Clock_Freq = SysCtlClockFreqSet( SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_25MHZ | SYSCTL_CFG_VCO_480, 80000000 );
    //Ddi_watchdog_init(); // Dis/enable led Watchdog near JTAG connector if set break the µC
    init_i2c();
    //configIO1();
    configIO2();

    value=0;
    value16=0;

	//exempleEEPROMnotinWhileLOOP();

    while(1)
    {
        //exampleChenillard(1);
        //exampleButtonPress();
	    //exempleButtonPressInt();
	    exempleIO2Chenillard(1,10);
    }
}
