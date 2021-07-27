#include "ddi_I2C_franck.h"

uint32_t var =0 ;

void InitI2C1(void)
{
    //enable I2C module 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C_USED);

    //reset module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C_USED);

    //enable GPIO peripheral that contains I2C 1
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);

    // Configure the pin muxing for I2C1 functions on port G0 and G1.
    GPIOPinConfigure(GPIO_PG0_I2C1SCL);
    GPIOPinConfigure(GPIO_PG1_I2C1SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTG_BASE, GPIO_PIN_0);
    GPIOPinTypeI2C(GPIO_PORTG_BASE, GPIO_PIN_1);

    // Enable and initialize the I2C1 master module.  Use the system clock for
    // the I2C1 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    var = SysCtlClockGet();
    I2CMasterInitExpClk(I2C_USED, SysCtlClockGet(), false);

    //clear I2C FIFOs
    HWREG(I2C_USED + I2C_O_FIFOCTL) = 80008000;
}

void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...)
{
    uint16_t i=0;
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C_USED, slave_addr, false);

    //stores list of variable number of arguments
    va_list vargs;

    //specifies the va_list to "open" and the last fixed argument
    //so vargs knows where to start looking
    va_start(vargs, num_of_args);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C_USED, va_arg(vargs, uint32_t));

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(num_of_args == 1)
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C_USED, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C_USED));

        //"close" variable argument list
        va_end(vargs);
    }
    else //otherwise, we start transmission of multiple bytes on the I2C bus
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C_USED, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C_USED));

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        for(i = 1; i < (num_of_args - 1); i++)
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C_USED, va_arg(vargs, uint32_t));
            //send next data that was just placed into FIFO
            I2CMasterControl(I2C_USED, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C_USED));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C_USED, va_arg(vargs, uint32_t));
        //send next data that was just placed into FIFO
        I2CMasterControl(I2C_USED, I2C_MASTER_CMD_BURST_SEND_FINISH);
        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C_USED));

        //"close" variable args list
        va_end(vargs);
    }

}

void I2CSendString(uint32_t slave_addr, char array[])
{
    // Tell the master module what address it will place on the bus when
    // communicating with the slave.
    I2CMasterSlaveAddrSet(I2C_USED, slave_addr, false);

    //put data to be sent into FIFO
    I2CMasterDataPut(I2C_USED, array[0]);

    //if there is only one argument, we only need to use the
    //single send I2C function
    if(array[1] == '\0')
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C_USED, I2C_MASTER_CMD_SINGLE_SEND);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C_USED));
    }

    //otherwise, we start transmission of multiple bytes on the
    //I2C bus
    else
    {
        //Initiate send of data from the MCU
        I2CMasterControl(I2C_USED, I2C_MASTER_CMD_BURST_SEND_START);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C_USED));

        //initialize index into array
        uint8_t i = 1;

        //send num_of_args-2 pieces of data, using the
        //BURST_SEND_CONT command of the I2C module
        while(array[i + 1] != '\0')
        {
            //put next piece of data into I2C FIFO
            I2CMasterDataPut(I2C_USED, array[i++]);

            //send next data that was just placed into FIFO
            I2CMasterControl(I2C_USED, I2C_MASTER_CMD_BURST_SEND_CONT);

            // Wait until MCU is done transferring.
            while(I2CMasterBusy(I2C_USED));
        }

        //put last piece of data into I2C FIFO
        I2CMasterDataPut(I2C_USED, array[i]);

        //send next data that was just placed into FIFO
        I2CMasterControl(I2C_USED, I2C_MASTER_CMD_BURST_SEND_FINISH);

        // Wait until MCU is done transferring.
        while(I2CMasterBusy(I2C_USED));
    }
}

//read specified register on slave device
uint32_t I2CReceive(uint32_t slave_addr, uint8_t reg)
{
    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C_USED, slave_addr, false);

    //specify register to be read
    I2CMasterDataPut(I2C_USED, reg);

    //send control byte and register address byte to slave device
    I2CMasterControl(I2C_USED, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C_USED));

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C_USED, slave_addr, true);

    //send control byte and read from the register we
    //specified
    I2CMasterControl(I2C_USED, I2C_MASTER_CMD_SINGLE_RECEIVE);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C_USED));

    //return data pulled from the specified register
    return I2CMasterDataGet(I2C_USED);
}

