
#include <ExEeprom.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "utility.h"
#include "ioExp.h"
#include "ioExp2.h"
#include "watchdog_ext.h"
#include "myFunctions.h"

// Définition global of µC speed
uint32_t HR_Sys_Clock_Freq;
int cpt,taille;
uint8_t value;
uint16_t value16;
uint32_t reply=0;
bool b;

void TestDriverI2CInterrupt(void)
{
	//Initialisation
	DdiScaleI2cInit();
	
	// Enable µC Interrupts
	IntMasterEnable();
		
	//EEPROM TEST
	//NOT_IN_LOOP_rw_eeprom_INT();
	//NOT_IN_LOOP_clearEeprom(0);
	//NIL_testExEepromRecover();

	tca9535.Config.all = 0x0000;
    tca9535.Output.all = 0x0003;
	DdiScaleI2cWrite(IOEXP2_ADDR, TCA9535_CONFIG_REG0, &tca9535.Config.ports.P0.all,1);
	DdiScaleI2cWrite(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, &tca9535.Output.ports.P0.all,1);

    while(1)
    {
		tca9535.Output.ports.P0.all ^= 0xFF;
        DdiScaleI2cWrite(IOEXP2_ADDR, TCA9535_OUTPUT_REG0, &tca9535.Output.ports.P0.all,1);
		if(!tca9535.Output.ports.P0.bit.B0)
			LOG("Led ON");
		else
			LOG("Led OFF");
        sleep_ms(1000);
    }
}

int main(void)
{
    HR_Sys_Clock_Freq = SysCtlClockFreqSet( SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_25MHZ | SYSCTL_CFG_VCO_480, 80000000 );

    Ddi_uart_Init();

	CLEAR_LOG; // => super usefull
    LOG(" *****Main Start *****");

	TestDriverI2CInterrupt();
}
