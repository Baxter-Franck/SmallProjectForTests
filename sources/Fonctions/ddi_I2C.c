#include "ddi_I2C.h"

void init_i2c(void)
{	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);	// Enable PORTG
	GPIOPinConfigure(GPIO_PG0_I2C1SCL); 			// Configure Alternate function for pin PG0
	GPIOPinConfigure(GPIO_PG1_I2C1SDA); 			// Configure Alternate function for pin PG1
	GPIOPinTypeI2CSCL(GPIO_PORTG_BASE, GPIO_PIN_0);	// Affect Pin PG0 at I2C SCL
	GPIOPinTypeI2C(GPIO_PORTG_BASE, GPIO_PIN_1);	// Affect Pin PG1 at I2C SDA
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);  	// Enable I2C1
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C1)); // utile ?
	
	I2CMasterInitExpClk(I2C1_BASE, HR_Sys_Clock_Freq, false);
	
	//clear I2C FIFOs
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;	
}

uint8_t i2c_Write(uint8_t slave_addr, uint16_t  valToSend, uint8_t reg)
{
	uint8_t success = TRUE;
	uint8_t erreurTransmission = FALSE;
	uint16_t timeOutI2C = 0;
	
	I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);
    I2CMasterDataPut(I2C1_BASE, reg);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    timeOutI2C = 0;
    //Wait for I2C reveive commande and pass to busy
    while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;

    timeOutI2C = 0;
    //while I2C is busy
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;

    // Check for errors.
    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
        erreurTransmission = TRUE;

    I2CMasterDataPut(I2C1_BASE,(uint8_t)valToSend);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
    timeOutI2C = 0;
    while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;

    // Check for errors.
    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
        erreurTransmission = TRUE;

	return success;
}

uint8_t i2c_Read(uint32_t * PData, uint32_t slave_addr, uint8_t reg)
{
    uint16_t timeOutI2C = 0;
    uint8_t erreurTransmission = FALSE;
    //clear I2C FIFOs
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;

    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);

    I2CMasterDataPut(I2C1_BASE, reg);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    timeOutI2C = 0;
    while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)
        return FALSE;

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)
        return FALSE;

    // Check for errors.
    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
        erreurTransmission = TRUE;

    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, true);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
    timeOutI2C = 0;
    while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)
        return FALSE;

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)
        return FALSE;

    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
    {
        //ERREUR I2C
        erreurTransmission = TRUE;
    }

    *PData = I2CMasterDataGet(I2C1_BASE);
    timeOutI2C = 0;
    while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)return FALSE;

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)
        return FALSE;

    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
        erreurTransmission = TRUE;

    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    return TRUE;
}

