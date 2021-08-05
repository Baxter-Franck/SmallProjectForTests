#include "Ticks.h"
#include "defines_HR.h"
#include "systick.h"

volatile uint32_t sysTickCounter_1ms=0;     /*1 miliseconds tick counter*/
volatile uint32_t sysTickCounter_10ms=0;    /*10 miliseconds tick counter*/
volatile uint32_t sysTickCounter_50ms=0;    /*50 miliseconds tick counter*/
volatile uint32_t sysTickCounter_100ms=0;   /*100 miliseconds tick counter*/
volatile uint32_t sysTickCounter_1s=0;      /*1 seconds tick counter*/
volatile uint16_t gTimCnt = 0;

void initTicks(void)
{
    SysTickPeriodSet(HR_Sys_Clock_Freq/1000);
    SysTickIntRegister(TickIntHandler);
    SysTickIntEnable();
    SysTickEnable();
}

void TickIntHandler(void)
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
            /*if(sysTickCounter_100ms ==  9)
            {
                sysTickCounter_100ms=0;
                sysTickCounter_1s++;
            }*/
            sysTickCounter_100ms++;
			sysTickCounter_1s = sysTickCounter_100ms/10; 
        }
        else
            sysTickCounter_10ms++;
    }
    else
        sysTickCounter_1ms++;
}
