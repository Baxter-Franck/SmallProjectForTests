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
#include "debug.h" // for ASSERT

// Définition global of µC speed
uint32_t HR_Sys_Clock_Freq;
int cpt,taille;
uint8_t value;
uint16_t value16;
uint32_t reply=0;
bool b;

int main(void)
{
    HR_Sys_Clock_Freq = SysCtlClockFreqSet( SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_25MHZ | SYSCTL_CFG_VCO_480, 80000000 );

    //Ddi_watchdog_init(); // Dis/enable led Watchdog near JTAG connector if set break the µC
    //init_i2c();
    //configIO1();
    //configIO2();

    InitI2C1_Franck();
	
    //config io
    tca9535.Config.ports.P0.all = 0x00;  // Port 0 as output
    tca9535.Config.ports.P1.all = 0x00;  // Port 1 as output
    tca9535.Output.all = 0x0003;

    //I2CSendFranck(IOEXP2_ADDR, TCA9535_CONFIG_REG0, 1, 0x00);
    //I2CSendFranck(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, 1, 0x03);

    value=0;
    value16=0;

	//exempleEEPROMnotinWhileLOOP();
	exempleEEPROMDriverFrancknotinWhileLOOP();

    while(1)
    {
        //exampleChenillard(1);
        //exampleButtonPress();
	    //exempleButtonPressInt();
	    //exempleIO2Chenillard(1,10);
        //exempleIO2ChenilladWithDriverFranck();

    }
}
