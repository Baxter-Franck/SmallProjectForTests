#include <ApiEeprom.h>
#include "debug.h"

void ApiInit_I2C_EEPREOM(void)
{
    DdiScaleI2cInit();
}

void ApiEepromWrite(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
	uint8_t ucSlaveAddr = ADDR_EEPROM | block;
    
	ASSERT(block<=7);
    ASSERT(address<=255);

   
    DdiScaleI2cWrite(ucSlaveAddr, address, pointer, length);

    if(DdiScaleI2cWriteVerify(ucSlaveAddr, address, pointer, length) == FALSE )
    {
        //Retry once
        DdiScaleI2cWrite(ucSlaveAddr, address, pointer, length);
        //Verify again
        if(DdiScaleI2cWriteVerify(ucSlaveAddr, address, pointer, length) == FALSE)
        {
            //NV_ERROR = 1;
            //ApiDiag_Set((ddidiag_code_T)(DDIDIAG_EEPROM_WRITE_ERR));
        }
    }

}


//code to implement writing critical data
//this routine write the data in 3 first block addresses passed... to use a single write use
//I2CWrite exemple bank=0 data = 1 the data 1 will write 1 in block0 block1 and block2
/*****************************************************************************/
/*  Example of how to write a byte to EEPROM */
/*****************************************************************************/
void ApiEepromWriteCritical(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
    uint8_t idx;
    for(idx=0; idx<3 ;idx++)
       ApiEepromWrite(idx, address, length, pointer);
}

uint8_t ApiEepromRead(uint8_t block, uint8_t address)
{
    ASSERT(block<=7);
    ASSERT(address<=255);
    return DdiScaleI2cRead1Byte(block, address);
}

