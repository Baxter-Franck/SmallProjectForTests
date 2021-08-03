#include "utility.h"

void uartPrint(const char *pcString, ...)
{
#ifdef DEBUG_ON_OFF
    va_list vaArgP;
    va_start(vaArgP, pcString);
    UARTvprintf(pcString, vaArgP);
    va_end(vaArgP);
#endif
}

void uartPrintln(const char *pcString, ...)
{
#ifdef DEBUG_ON_OFF
    va_list vaArgP;
    va_start(vaArgP, pcString);
    UARTvprintf(pcString, vaArgP);
    va_end(vaArgP);
    UARTvprintf("\n",vaArgP);
#endif
}

void __error__(char *pcFilename, uint32_t ui32Line)
{
    LOG("##### ==> ERROR in %s[L:%d]",pcFilename,ui32Line);
}
