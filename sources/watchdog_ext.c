#include "watchdog_ext.h"

void Ddi_watchdog_init(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
	GPIOPinTypeGPIOOutput(GPIO_PORTK_BASE, GPIO_PIN_0);
	Ddi_watchdog_set();
	Ddi_watchdog_reset();
}

void Ddi_watchdog_set(void)
{
	//Set
	GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, 1);
}

void Ddi_watchdog_reset(void)
{
	//Set
	GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0, 0);
}
