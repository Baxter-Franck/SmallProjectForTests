#include <ddi_scale_eeprom_i2c.h>

// The variables that track the data to be transmitted or received.
PRIVATE uint8_t *g_pucData = 0;
PRIVATE uint32_t g_ulCount = 0;
PRIVATE uint8_t g_ucSlaveAddress = 0;
volatile PRIVATE uint32_t g_ulErr = 0;
PRIVATE uint8_t g_ucI2C_ERROR = 0;

// The current state of the interrupt handler state machine.
PRIVATE volatile STATE_INT_EEPROM g_StateEp = STATE_IDLE;

/**************************************************************************
DOES:    The I2C_Init function. Initializes the I2C1 for EEPROM
RETURNS: nothing
 **************************************************************************/
void DdiScaleEepromI2cInit(void)
{
    uint32_t speed = 0;

    // Turn on I2C1 and the GPIO port whose pins it will use.
    MAP_SysCtlPeripheralEnable(SCALE_EEPROM_PERIPH_GPIO);
    MAP_SysCtlPeripheralEnable(SCALE_EEPROM_PERIPH_I2C);

    // Configure the Port pins for I2C1
    GPIOPinConfigure(SCALE_EEPROM_GPIO_ALT_I2C1_SCL);
    GPIOPinConfigure(SCALE_EEPROM_GPIO_ALT_I2C1_SDA);

    GPIOPinTypeI2CSCL(SCALE_EEPROM_GPIO_PORT, SCALE_EEPROM_PIN_SCL);
    GPIOPinTypeI2C(SCALE_EEPROM_GPIO_PORT, SCALE_EEPROM_PIN_SDA);

    // Enable and Initialize Master module and Master Clock using 100kbps or 400kbps
    // based on FastSpeed flag (FastSpeed = 0 -> 100kbps; FastSpeed = 1 -> 400kbps)
    speed = HR_Sys_Clock_Freq;  // Ne fonctionne pas avec ca
    speed = SysCtlClockGet();   // BUGF: fonctionne avec ca ! or on ne doit pas utilise SysCtlClockGet() avec un TM4C129 ! ? !
    I2CMasterInitExpClk(SCALE_EEPROM_I2C_MASTER, speed, 0);

    IntPrioritySet(SCALE_EEPROM_INT , 0x1);
    IntRegister(SCALE_EEPROM_INT, DdiScaleEepromI2cIntHandler);  //INFO: We can declare Interrupt Here of comment and declare in startup_TM4C129.s
    IntEnable(SCALE_EEPROM_INT);
    //Enable I2C master interrupt
    I2CMasterIntEnable(SCALE_EEPROM_I2C_MASTER);
}


//*****************************************************************************
//
// The I2C interrupt handler.
//
//*****************************************************************************
void DdiScaleEepromI2cIntHandler(void)
{
    // Clear the I2C interrupt.
    I2CMasterIntClear(SCALE_EEPROM_I2C_MASTER);

    // Determine what to do based on the current state.
    switch(g_StateEp)
    {
    // The idle state.
    case STATE_IDLE: 
    {
        // There is nothing to be done.
        break;
    }
    // The state for the middle of a burst write.
    case STATE_WRITE_NEXT: 
    {
        // Write the next byte to the data register.
        I2CMasterDataPut(SCALE_EEPROM_I2C_MASTER, *g_pucData++);
        g_ulCount--;
        // Continue the burst write.
        I2CMasterControl(SCALE_EEPROM_I2C_MASTER, I2C_MASTER_CMD_BURST_SEND_CONT);
        // If there is one byte left, set the next state to the final write
        // state.
        if(g_ulCount == 1)
        {
            g_StateEp = STATE_WRITE_FINAL;
        }
        break;
    }
    // The state for the final write of a burst sequence.
    case STATE_WRITE_FINAL: 
    {
        // Write the final byte to the data register.
        I2CMasterDataPut(SCALE_EEPROM_I2C_MASTER, *g_pucData++);
        g_ulCount--;
        // Finish the burst write.
        I2CMasterControl(SCALE_EEPROM_I2C_MASTER,I2C_MASTER_CMD_BURST_SEND_FINISH);
        // The next state is to wait for the burst write to complete.
        g_StateEp = STATE_SEND_ACK;
        // This state is done.
        break;
    }
    // Wait for an ACK on the read after a write.
    case STATE_WAIT_ACK:
    {
        // See if there was an error on the previously issued read.
        if(I2CMasterErr(SCALE_EEPROM_I2C_MASTER) == I2C_MASTER_ERR_NONE)
        {
            // Read the byte received.
            //I2CMasterDataGet(EEP_I2C_MASTER_BASE);
            // There was no error, so the state machine is now idle.
            g_StateEp = STATE_IDLE;
            // This state is done.
            break;
        }
        // Fall through to STATE_SEND_ACK.
    }
    // Send a read request, looking for the ACK to indicate that the write
    // is done.
    case STATE_SEND_ACK: 
    {
        // Put the I2C master into receive mode.
        I2CMasterSlaveAddrSet(SCALE_EEPROM_I2C_MASTER, g_ucSlaveAddress, false);
        // Perform a single byte read.
        I2CMasterControl(SCALE_EEPROM_I2C_MASTER, I2C_MASTER_CMD_SINGLE_SEND);
        // The next state is the wait for the ack.
        g_StateEp = STATE_WAIT_ACK;
        // This state is done.
        break;
    }
    // The state for a single byte read.
    case STATE_READ_ONE: 
    {
        // Put the I2C master into receive mode.
        I2CMasterSlaveAddrSet(SCALE_EEPROM_I2C_MASTER, g_ucSlaveAddress, true);
        // Perform a single byte read.
        I2CMasterControl(SCALE_EEPROM_I2C_MASTER, I2C_MASTER_CMD_SINGLE_RECEIVE);
        // The next state is the wait for final read state.
        g_StateEp = STATE_READ_WAIT;
        // This state is done.
        break;
    }
    // The state for the start of a burst read.
    case STATE_READ_FIRST:
    {
        // Put the I2C master into receive mode.
        I2CMasterSlaveAddrSet(SCALE_EEPROM_I2C_MASTER, g_ucSlaveAddress, true);
        // Start the burst receive.
        I2CMasterControl(SCALE_EEPROM_I2C_MASTER,I2C_MASTER_CMD_BURST_RECEIVE_START);
        // The next state is the middle of the burst read.
        if(g_ulCount == 2)
        {
            // If there are two characters left to be read, make the next
            // state be the end of burst read state.
            g_StateEp = STATE_READ_FINAL;
        }
        else
        {
            g_StateEp = STATE_READ_NEXT;
        }
        break;
    }
    // The state for the middle of a burst read.
    case STATE_READ_NEXT: 
    {
        // Read the received character.
        *g_pucData++ = I2CMasterDataGet(SCALE_EEPROM_I2C_MASTER);
        g_ulCount--;
        // Continue the burst read.
        I2CMasterControl(SCALE_EEPROM_I2C_MASTER,I2C_MASTER_CMD_BURST_RECEIVE_CONT);
        // If there are two characters left to be read, make the next
        // state be the end of burst read state.
        if(g_ulCount == 2)
        {
            g_StateEp = STATE_READ_FINAL;
        }
        break;
    }
    // The state for the end of a burst read.
    case STATE_READ_FINAL: 
    {
        // Read the received character.
        *g_pucData++ = I2CMasterDataGet(SCALE_EEPROM_I2C_MASTER);
        g_ulCount--;
        // Finish the burst read.
        I2CMasterControl(SCALE_EEPROM_I2C_MASTER,I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
        // The next state is the wait for final read state.
        g_StateEp = STATE_READ_WAIT;
        break;
    }
    // This state is for the final read of a single or burst read.
    case STATE_READ_WAIT: 
    {
        // Read the received character.
        *g_pucData++  = I2CMasterDataGet(SCALE_EEPROM_I2C_MASTER);
        g_ulCount--;
        // The state machine is now idle.
        g_StateEp = STATE_IDLE;
        // This state is done.
        break;
    }

    default:
        break;
    }
}


//*****************************************************************************
//
// Write to the EEPROM.
//
//*****************************************************************************
uint8_t DdiScaleEepromI2cWrite(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData, uint32_t ulCount)
{
	g_ucI2C_ERROR = 0;
    // Save the data buffer to be written.
    g_pucData = pucData;
    g_ulCount = ulCount;

    // Set the next state of the interrupt state machine based on the number of
    // bytes to write.
    if(ulCount != 1) 
    {
        g_StateEp = STATE_WRITE_NEXT;
    }
    else
    {
        g_StateEp = STATE_WRITE_FINAL;
    }
    // Set the slave address and setup for a transmit operation.
    I2CMasterSlaveAddrSet(SCALE_EEPROM_I2C_MASTER, ucSlv_Addr, FALSE);
    // Place the address to be written in the data register.
    I2CMasterDataPut(SCALE_EEPROM_I2C_MASTER, ucRegister);
    // Start the burst cycle, writing the address as the first byte.
    I2CMasterControl(SCALE_EEPROM_I2C_MASTER, I2C_MASTER_CMD_BURST_SEND_START);
    // Wait until the I2C interrupt state machine is idle.
    g_ulErr = 0;
    while((g_StateEp != STATE_IDLE) && (g_ulErr < DDI_EEPROM_MAXRETRY))
    {
        g_ulErr++;
    }

    if(g_ulErr >= DDI_EEPROM_MAXRETRY)
    {
        g_ucI2C_ERROR = 1;
    }
	return g_ucI2C_ERROR; 
}

//*****************************************************************************
//
// Read from the EEPROM
//
//*****************************************************************************
uint8_t DdiScaleEepromI2cRead(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData, uint32_t ulCount)
{
	g_ucI2C_ERROR = 0;
    // Save the data buffer to be read.
    g_pucData = pucData;
    g_ulCount = ulCount;
    g_ucSlaveAddress = ucSlv_Addr;
    // Set the next state of the interrupt state machine based on the number of
    // bytes to read.
    if(ulCount == 1) 
    {
        g_StateEp = STATE_READ_ONE;
    }
    else
    {
        g_StateEp = STATE_READ_FIRST;
    }
    // Start with a dummy write to get the address set in the EEPROM.
    I2CMasterSlaveAddrSet(SCALE_EEPROM_I2C_MASTER, ucSlv_Addr, FALSE);
    // Place the address to be written in the data register.
    I2CMasterDataPut(SCALE_EEPROM_I2C_MASTER, ucRegister);
    // Perform a single send, writing the address as the only byte.
    I2CMasterControl(SCALE_EEPROM_I2C_MASTER, I2C_MASTER_CMD_SINGLE_SEND);
    // Wait until the I2C interrupt state machine is idle.
    g_ulErr = 0;
    while((g_StateEp != STATE_IDLE) && (g_ulErr < DDI_EEPROM_MAXRETRY))
    {
        g_ulErr++;
    }

    if(g_ulErr >= DDI_EEPROM_MAXRETRY)
    {
        g_ucI2C_ERROR = 1;
    }
	return g_ucI2C_ERROR;
}

//*****************************************************************************
//
// Verify a location.
//
//*****************************************************************************
/*PUBLIC BOOLEAN DdiEepI2cWriteVerify(UNSIGNED8 ucSlv_Addr, UNSIGNED8 *pucData, UNSIGNED32 ulOffset,UNSIGNED32 ulCount)
{
    UNSIGNED8 i,ucData[4] = {0};
    BOOLEAN result = TRUE;
    if(ulCount > sizeof(UNSIGNED32))
    {
        result = FALSE;
    }
    else
    {
        //Verify if the write through correctly
        DdiEepI2cRead(ucSlv_Addr,(UNSIGNED8 *)&ucData,ulOffset,ulCount);
        for(i=0;i<ulCount;i++)
        {
            if(ucData[i] != pucData[i])
            {
                result = FALSE;
                break;
            }
        }
    }
    return result;
}*/
