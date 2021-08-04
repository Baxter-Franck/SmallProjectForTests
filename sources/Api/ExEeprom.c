/**
 * @file ExEeprom.c
 * @details  This file is an API for access to ExEprom I2C for Scale requirement.\n
 * In this case used for merging SCB code into ICB.
 * @author Franck FURIC
 * @version 1.0
 * @date 03/08/2021
 * @copyright 2018 HillRom\n
 * All Rights Reserved.\n
 * The information contained herein is confidential
 * property of Hill-Rom. The user, copying, transfer or
 * disclosure of such information is prohibited except
 * by express written agreement with Hill-Rom.
 */

#include <ExEeprom.h>

uint8_t  UC_I2C_ERROR;


/**
 * @brief   Initialisation of EEPROM I2C
 */
void ExEEPROM_Init(void)
{
    DdiScaleI2cInit();
}

/**
 * @param        block: Block of EEPROM
 * @param        address: address in block
 * @param        length: size of data to write in eeprom <= 16
 * @param        pointer: point of data
 * @brief        This function writes in EEPROM.
 *               In 24LC16B we can't R/W more than 16 byte in a row !
 *               length not exceed 16 bytes
 */
void ExEEPROM_Write(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
    uint8_t ucSlaveAddr = ADDR_EEPROM | block;
    ASSERT(ucSlaveAddr>=0x50 && ucSlaveAddr<=0x57);
    ASSERT(length<=16); //In 24LC16B we can't R/W more than 16 byte in a row !

    DdiScaleI2cWrite(ucSlaveAddr, address, pointer, length);

    if(ExEEPROM_WriteVerify(ucSlaveAddr, address, pointer, length) == FALSE )
    {
        //Retry once
        DdiScaleI2cWrite(ucSlaveAddr, address, pointer, length);
        //Verify again
        if(ExEEPROM_WriteVerify(ucSlaveAddr, address, pointer, length) == FALSE)
        {
            //NV_ERROR = 1;
            //ApiDiag_Set((ddidiag_code_T)(DDIDIAG_EEPROM_WRITE_ERR));
        }
    }
}

/**
 * \param        block: Block of EEPROM
 * \param        address: address in block
 * \param        length: size of data to write in eeprom <= 16
 * \param        pointer: point of data
 * \return
 * \brief        This function writes in EEPROM.
 *              In 24LC16B we can't R/W more than 16 byte in a row !
 *               length not exceed 16 bytes
 */
void ExEEPROM_WriteCritic(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
    uint8_t idx;
    for(idx=0; idx<3 ;idx++)
        ExEEPROM_Write(idx, address, length, pointer);
}


/**
 * @param        block: Block of EEPROM
 * @param        address: address in block
 * @param        length: size of data to write in eeprom <= 16
 * @param[out]   pointer: point of data
 * @retval       0: => OK
 * @retval       1: => NOK
 * @brief        This function read in EEPROM.
 *               In 24LC16B we can't R/W more than 16 byte in a row !
 *               length not exceed 16 bytes
 */
uint8_t ExEEPROM_Read(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
    uint8_t ucSlaveAddr = ADDR_EEPROM | block;
    ASSERT(ucSlaveAddr>=0x50 && ucSlaveAddr<=0x57);
    ASSERT(length<=16); //In 24LC16B we can't R/W more than 16 byte in a row !
    return DdiScaleI2cRead(ucSlaveAddr, address, pointer, length);
}

/**
 * @param block of reading eeprom
 * @param address of reading
 * @param length size of data to write in eeprom <= 16
 * @param[out] pointer Value contain data
 * @return 2 if good reading
 * @details This function read the same data place in 3 block [0,1,2] at the same address these 3 value must be the same
 * value or trig an error.
 */
uint8_t ExEEPROM_ReadCritic(uint8_t block, uint8_t address, uint8_t length, void* pointer)
{
    uint8_t *destination_pointer=0;//destination pointer
    uint8_t *temp_pointer=0;//Temp pointer
    uint8_t temp_char=0;//Temp char
    uint8_t j=0;//index
    uint8_t temp[3];

    //use the largest size variable and set all bytes to 0
    for(j=0;j<3;++j)
    {
        temp[j]=0;
    }
    //read all 3 address
    for(j=0;j<3;++j)
    {
        ExEEPROM_Read(j,address,length,&temp[j]);
    }

    //check to see if the variables are the same
    if(temp[0] != temp[1])
    {
        //temp2 = temp0.. so temp1 must be bad
        if(temp[0]==temp[2])
        {
            //Write address2 with the data from address1
            ExEEPROMRecover(0x01,address,length,&temp[0],&temp[1]);
            //check to see if the recovery worked
            if(temp[0] !=temp[1])
            {
                UC_I2C_ERROR |= I2C_EE_RECOVERY;
                return 0;
            }
        }

        //temp1 = temp2.. so temp0 must be bad
        else if(temp[1] == temp[2])
        {
            //Write address1 with the data from address2
            ExEEPROMRecover(0x00,address,length,&temp[1],&temp[0]);
            //cehck to see if the recovery worked
            if(temp[0] !=temp[1])
            {
                UC_I2C_ERROR |= I2C_EE_RECOVERY;
                return 0;
            }
        }

        // IDB: NPD0184A, I:472; If 3 Corrupt E^2 data detected, system couldn't recover because
        // EEPROM was no longer allowed to be accessed.  Now comparison to GENERAL_EEPROM_ERRORS
        // is made, of which I2C_ALL_3_ADDRESSES_BAD is a member.
        //nobody matches.....
        else
        {
            UC_I2C_ERROR |= I2C_ALL_3_ADDRESSES_BAD;
            return 0;
        }
    }
    else if(temp[0] == temp[1])
    {
        //temp0 = temp2.. so temp2 must be bad
        if(temp[0] != temp[2])
        {
            //Write address3 with the data from address1
            ExEEPROMRecover(0x02,address,length,&temp[0],&temp[2]);
            //check to see if the recovery worked
            if(temp[0] != temp[2])
            {
                //UC_I2C_ERROR |= I2C_EE_RECOVERY;
                return 0;
            }
        }
    }

    //if everything was ok copy what is in temp1 to what
    destination_pointer = (UNSIGNED8 *) pointer;
    temp_pointer = (UNSIGNED8 *) &temp[0];
    for(j=0;j<length;++j)
    {
        //advance for worst case 4 byte read
        temp_char = *temp_pointer;
        *destination_pointer = temp_char;
        ++destination_pointer;
        ++temp_pointer;
    }
    return 2;
}

/**
 * @param ucSlv_Addr Address of I2C peripheric
 * @param ucRegister Address od register to be Read
 * @param pucData    Pointer of data to store
 * @param ulCount    Size of data to read
 * @retval true => OK
 * @retval false => NOK
 * @brief This function verify if content of pointer pucData is the same in eeprom
 */
BOOLEAN ExEEPROM_WriteVerify(uint8_t ucSlv_Addr, uint8_t ucRegister, uint8_t *pucData,uint32_t ulCount)
{
    uint8_t i,ucData[4] = {0};
    if(ulCount > sizeof(uint32_t))
    {
        return FALSE;
    }
    else
    {
        //Verify if the write through correctly
        DdiScaleI2cRead(ucSlv_Addr, ucRegister, ucData, ulCount);
        for(i=0;i<ulCount;i++)
        {
            if(ucData[i] != pucData[i])
                return FALSE;
        }
    }
    return TRUE;
}

/**
 * @param block of reading eeprom
 * @param address of reading
 * @param length size of data to write in eeprom <= 16
 * @param write_pointer value to be writ on read_pointer
 * @param[out] read_pointer recover data
 * @brief This function write one address X and read it in read_pointer
 */
void ExEEPROMRecover(uint8_t block, uint8_t address, uint8_t length, void *write_pointer, void *read_pointer)
{
    //try to re-write the corrupt address
    ExEEPROM_Write(block, address, length, write_pointer);
    //then read it back
    ExEEPROM_Read(block, address, length, read_pointer);
}

