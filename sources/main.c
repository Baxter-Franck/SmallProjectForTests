
#include <ExEeprom.h>
#include "sysctl.h"
#include "systick.h"
#include "hw_memmap.h"
#include "utility.h"
#include "ioExp.h"
#include "ioExp2.h"
#include "watchdog_ext.h"
#include "myFunctions.h"

/* ticks */
volatile uint32_t sysTickCounter_1ms=0;		/*1 miliseconds tick counter*/
volatile uint32_t sysTickCounter_10ms=0; 	/*10 miliseconds tick counter*/
volatile uint32_t sysTickCounter_50ms=0;	/*50 miliseconds tick counter*/
volatile uint32_t sysTickCounter_100ms=0;	/*100 miliseconds tick counter*/
volatile uint32_t sysTickCounter_1s=0;		/*1 seconds tick counter*/
volatile uint16_t gTimCnt = 0;
/*********/

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

    IOExp2.Config.all = 0x0000;
    IOExp2.Output.all = 0xFF03;
    ioExp2Write(TCA9535_CONFIG_REG0, IOExp2.Config.all);
    ioExp2Write(TCA9535_OUTPUT_REG0, IOExp2.Output.all);

    while(1)
    {
        IOExp2.Output.ports.P0.all ^= 0xFF;
        ioExp2Write(TCA9535_OUTPUT_REG0, IOExp2.Output.all);
        if(!IOExp2.Output.ports.P0.bit.B0)
            LOG("Led ON  [0x%x]",IOExp2.Output.all);
        else
            LOG("Led OFF [0x%x]",IOExp2.Output.all);

		LOG("sysTickCounter_1s    => %d",sysTickCounter_1s);
        sleep_ms(1000);
    }
}

// cela fonctionne faire un fichier avec un systick pour compure une minute seconde sysTickCounter_1s donne le secondes passé.
void SysTickIntHandler(void)
{
	//Manage gTimCnt.
	//This counter is used as an auxiliary counter for CANOpen tasks
	gTimCnt++;
	//Manage sysTickCounter_1ms and sysTickCounter_10ms.
	//sysTickCounter_1ms increments of 1 unit every 1 ms from 0 to 9
	//sysTickCounter_10ms increments of 1 unit every 10 ms
	//sysTickCounter_1s increments of 1 unit every 100 ms
	if(sysTickCounter_1ms==9)
	{
		sysTickCounter_1ms=0;
		if(sysTickCounter_10ms==9)
		{
			sysTickCounter_10ms=0;
			if(sysTickCounter_100ms==9)
			{
				sysTickCounter_100ms=0;
				sysTickCounter_1s++;
			}
			else
				sysTickCounter_100ms++;
		}
		else
			sysTickCounter_10ms++;
	}
	else
		sysTickCounter_1ms++;
}

int main(void)
{
    HR_Sys_Clock_Freq = SysCtlClockFreqSet( SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_25MHZ | SYSCTL_CFG_VCO_480, 80000000 );

    SysTickPeriodSet(HR_Sys_Clock_Freq/1000);
	SysTickIntRegister(SysTickIntHandler);
	SysTickIntEnable();
    SysTickEnable();
	
	IntMasterEnable();

    Ddi_uart_Init();
	CLEAR_LOG; // => super usefull
   
	LOG(" *****Main Start *****");
    LOG("sysTickCounter_100ms => %d",sysTickCounter_100ms);
	LOG("sysTickCounter_10ms  => %d",sysTickCounter_10ms);
	LOG("sysTickCounter_1ms  => %d",sysTickCounter_1ms);
 
    TestDriverI2CInterrupt();
}
