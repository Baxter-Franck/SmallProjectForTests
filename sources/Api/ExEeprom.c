#include <ExEeprom.h>

/**************************************************
* \name      EEPREOM_I2C_Init
* \return
* \author    Franck FURIC
* \date      aout 2021
* \brief     This function init the eeprom for storing scale variable.
**************************************************/
void ExEEPROM_Init(void)
{
    DdiScaleI2cInit();
}

/**************************************************
* \name         EEPROM_Write
* \param        block: Block of EEPROM
* \param        address: address in block
* \param        length: size of data to write in eeprom <= 16
* \param        pointer: point of data
* \return
* \author       Franck FURIC
* \date         aout 2021
* \brief        This function writes in EEPROM.
* \details      In 24LC16B we can't R/W more than 16 byte in a row !
*               length not exceed 16 bytes
**************************************************/
void ExEEPROM_Write(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
	uint8_t ucSlaveAddr = ADDR_EEPROM | block;
    
	ASSERT(block>=0x50 && block<=0x57);
    ASSERT(address<=255);
    ASSERT(length<=16); //In 24LC16B we can't R/W more than 16 byte in a row !
   
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

/**************************************************
* \name         EEPROM_WriteCritic
* \param        block: Block of EEPROM
* \param        address: address in block
* \param        length: size of data to write in eeprom <= 16
* \param        pointer: point of data
* \return
* \author       Franck FURIC
* \date         aout 2021
* \brief        This function writes in EEPROM.
* \details      In 24LC16B we can't R/W more than 16 byte in a row !
*               length not exceed 16 bytes
**************************************************/
void ExEEPROM_WriteCritic(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
    uint8_t idx;
    for(idx=0; idx<3 ;idx++)
       ExEEPROM_Write(idx, address, length, pointer);
}

/**************************************************
* \name         EEPROM_Read
* \param        block: Block of EEPROM
* \param        address: address in block
* \param        length: size of data to write in eeprom <= 16
* \param        pointer: point of data
* \return       0 => OK
*               1 => NOK
* \author       Franck FURIC
* \date         aout 2021
* \brief        This function read in EEPROM.
* \details      In 24LC16B we can't R/W more than 16 byte in a row !
*               length not exceed 16 bytes
**************************************************/
uint8_t ExEEPROM_Read(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
    ASSERT(block>=0x50 && block<=0x57);
    ASSERT(address<=255);
    ASSERT(length<=16); //In 24LC16B we can't R/W more than 16 byte in a row !

    return DdiScaleI2cRead(block, address, pointer, length);
}

