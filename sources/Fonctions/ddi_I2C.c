#include "ddi_I2C.h"

const uint32_t WAIT = 0x7000;

void init_i2c(void)
{	
    uint32_t speed=0;
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);	// Enable PORTG
	SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);      //Reset I2C1
	GPIOPinConfigure(GPIO_PG0_I2C1SCL); 			// Configure Alternate function for pin PG0
	GPIOPinConfigure(GPIO_PG1_I2C1SDA); 			// Configure Alternate function for pin PG1
	GPIOPinTypeI2CSCL(GPIO_PORTG_BASE, GPIO_PIN_0);	// Affect Pin PG0 at I2C SCL
	GPIOPinTypeI2C(GPIO_PORTG_BASE, GPIO_PIN_1);	// Affect Pin PG1 at I2C SDA
	SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);  	// Enable I2C1
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_I2C1)); // utile ?
	
	speed = HR_Sys_Clock_Freq;
	//speed = SysCtlClockGet();
	I2CMasterInitExpClk(I2C1_BASE, speed, false);
	
	//I2CMasterTimeoutSet(I2C1_BASE, 0x7d); //Franck: en ajoutant ca, plus besoin de pause mais je ne sais pas comment ca fonctionne.

	//clear I2C FIFOs
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;	
}

uint8_t i2c_Write(uint8_t slave_addr, uint16_t  valToSend, uint8_t reg)
{
    uint16_t timeOutI2C = 0;
    //clear I2C FIFOs
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;

	I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, false);
    I2CMasterDataPut(I2C1_BASE, reg);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START);
    timeOutI2C = 0;
    //Wait for I2C reveive commande and pass to busy
    /*while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)
        return I2C_ERROR_TIMEOUT_1;*/

    timeOutI2C = 0;
    //while I2C is busy
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <WAIT)timeOutI2C++;
    if(timeOutI2C>=WAIT)
        return I2C_ERROR_TIMEOUT_2;

    // Check for errors.
    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
        return I2C_ERROR_MASTER;

    I2CMasterDataPut(I2C1_BASE,(uint8_t)valToSend);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);

    timeOutI2C = 0;
    /*while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)
        return I2C_ERROR_TIMEOUT_3;*/

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <WAIT)timeOutI2C++;
    if(timeOutI2C>=WAIT)
        return I2C_ERROR_TIMEOUT_4;

    // Check for errors.
    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
        return I2C_ERROR_MASTER;

	return I2C_NO_ERROR;
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
    /*while(!I2CMasterBusy(I2C1_BASE) && timeOutI2C <2000)timeOutI2C++;
    if(timeOutI2C>=2000)
        return FALSE;*/

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <WAIT)timeOutI2C++;
    if(timeOutI2C>=WAIT)
        return FALSE;

    // Check for errors.
    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
        erreurTransmission = TRUE;

    I2CMasterSlaveAddrSet(I2C1_BASE, slave_addr, true);
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);


    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <WAIT)timeOutI2C++;
    if(timeOutI2C>=WAIT)
        return FALSE;

    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
    {
        //ERREUR I2C
        erreurTransmission = TRUE;
    }

    *PData = I2CMasterDataGet(I2C1_BASE);

    timeOutI2C = 0;
    while(I2CMasterBusy(I2C1_BASE) && timeOutI2C <WAIT)timeOutI2C++;
    if(timeOutI2C>=WAIT)
        return FALSE;

    if( I2CMasterErr(I2C1_BASE) != I2C_MASTER_ERR_NONE)
        erreurTransmission = TRUE;

    //I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

    return TRUE;
}

