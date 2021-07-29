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

void TestDriverI2CFranck(void)
{
	//Initialisation
	InitI2C1_Franck();
	
	exempleEEPROMDriverFrancknotinWhileLOOP();
	
	tca9535.Config.all = 0x0000;
	tca9535.Output.all = 0x0003;
	I2CSendFranck(IOEXP2_ADDR, TCA9535_CONFIG_REG0, 1, tca9535.Config.ports.P0.all);
	I2CSendFranck(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, 1, tca9535.Output.ports.P0.all);
	
	while(1)
    {
		tca9535.Output.ports.P0.all ^= 0xFF;
        I2CSendFranck(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, 1, tca9535.Output.ports.P0.all);
        sleep_ms(50);
    }
}

void TestDriverI2CInterrupt(void)
{
	//Initialisation
	DdiScaleEepromI2cInit();
	
	// Enable µC Interrupts
	IntMasterEnable();
	
	sleep_ms(50);
	
	exempleDDI_EEPROM_INTERRUP_notinWhileLOOP();

	tca9535.Config.all = 0x0000;
    tca9535.Output.all = 0x0003;
	DdiScaleEepromI2cWrite(IOEXP2_ADDR, TCA9535_CONFIG_REG0, &tca9535.Config.ports.P0.all,1);
	DdiScaleEepromI2cWrite(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, &tca9535.Output.ports.P0.all,1);

    while(1)
    {
		tca9535.Output.ports.P0.all ^= 0xFF;
        DdiScaleEepromI2cWrite(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, &tca9535.Output.ports.P0.all,1);
        sleep_ms(50);
    }
}

int main(void)
{
    HR_Sys_Clock_Freq = SysCtlClockFreqSet( SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_25MHZ | SYSCTL_CFG_VCO_480, 80000000 );

    //Ddi_watchdog_init(); // Dis/enable led Watchdog near JTAG connector if set break the µC
    //init_i2c();
    //configIO1();
    //configIO2();

	
	//TestDriverI2CFranck();
	TestDriverI2CInterrupt();
	   
}
