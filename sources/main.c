#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include "sysctl.h"
#include "hw_memmap.h"
#include "ioExp.h"
#include "watchdog_ext.h"
#include "myFunctions.h"

// Définition global of µC speed
uint32_t HR_Sys_Clock_Freq;
int cpt,taille;
uint8_t value;

int main(void)
{
	HR_Sys_Clock_Freq = SysCtlClockFreqSet( SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_XTAL_25MHZ | SYSCTL_CFG_VCO_480, 80000000 );
	//Ddi_watchdog_init(); // Dis/enable led Watchdog near JTAG connector if set break the µC
	Ddi_ioexp_Init();
	
	chenillard(1);
}
