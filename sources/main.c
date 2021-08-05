
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

        LOG("sysTickCounter_1s       => %d",sysTickCounter_1s);
        LOG("sysTickCounter_100ms    => %d",sysTickCounter_100ms);
        sleep_ms(1000);
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
