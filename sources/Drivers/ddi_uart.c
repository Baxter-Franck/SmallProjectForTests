#include "sysctl.h"                 // SysCtlPeripheralEnable
#include "pin_map.h"                // GPIO_PC6_U5RX
#include "gpio.h"                   // GPIOPinConfigure
#include "hw_memmap.h"              // GPIO_PORTC_BASE
#include "defines_HR.h"             // Clock HR_Sys_Clock_Freq
#include "uart.h"                   // Config UART

#define UART_DEBUG_BASE             UART5_BASE
#define SYSCTL_PERIPH_GPIO_UART5    SYSCTL_PERIPH_GPIOC
#define SYSCTL_PERIPH_UART_DEBUG    SYSCTL_PERIPH_UART5

#define GPIO_PORT_UART_DEBUG_BASE   GPIO_PORTC_BASE
#define PIN_RX_UART5                GPIO_PIN_6
#define PIN_TX_UART5                GPIO_PIN_7
#define PIN_RX_UART5_CONFIG         GPIO_PC6_U5RX
#define PIN_TX_UART5_CONFIG         GPIO_PC7_U5TX

void Ddi_uart_Init(void)
{
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_UART_DEBUG );
    SysCtlPeripheralEnable ( SYSCTL_PERIPH_GPIO_UART5 );
    GPIOPinConfigure ( PIN_RX_UART5_CONFIG );
    GPIOPinConfigure ( PIN_TX_UART5_CONFIG );
    GPIOPinTypeUART ( GPIO_PORT_UART_DEBUG_BASE, PIN_RX_UART5 | PIN_TX_UART5 );

    UARTConfigSetExpClk ( UART_DEBUG_BASE, HR_Sys_Clock_Freq,
        115200,
        ( UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE ) );

    UARTEnable ( UART_DEBUG_BASE );
}


