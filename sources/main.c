
#include <ExEeprom.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "utility.h"
#include "ioExp.h"
#include "ioExp2.h"
#include "watchdog_ext.h"
#include "myFunctions.h"
#include "Ticks.h"

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

    IOExp2.all = 0xFF03;
	configIOExp2();

    while(1)
    {
		exempleIO2Chenillard(1,25);
        LOG("sysTickCounter_1s       => %d",sysTickCounter_1s);
    }
}

int main(void)
{
    HR_Sys_Clock_Freq = SysCtlClockFreqSet( SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_25MHZ | SYSCTL_CFG_VCO_480, 80000000 );

    Ddi_uart_Init();
    CLEAR_LOG; // => super usefull

    initTicks();
    IntMasterEnable();

    LOG(" *****Main Start *****");

    TestDriverI2CInterrupt();
}
