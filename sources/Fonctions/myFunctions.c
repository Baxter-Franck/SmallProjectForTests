#include "myFunctions.h"

void GPIOL_Handler(void);

extern int cpt,taille;
extern uint8_t value;
uint8_t valueLed;
uint16_t i;
uint32_t rxByte;
const uint16_t size = 10;
uint8_t array[size];
uint8_t array1[size];
uint8_t array2[size];

void NOT_IN_LOOP_rw_eeprom_INT(void)
{	
    memset(array, 42, sizeof(array)); // init array at 0
    memset(array1, 43, sizeof(array1)); // init array at 0
    memset(array2, 44, sizeof(array2)); // init array at 0

    i=0;
    // ecriture en eeprom BLOCK_0 et BLOCK_1
    for(i=0; i<size ;i++)
        array[i] = DdiScaleI2cWrite1Byte(ADDR_EEPROM_BLOCK_0, i, 10+i);

    for(i=0; i<size ;i++)
        array1[i] = DdiScaleI2cWrite1Byte(ADDR_EEPROM_BLOCK_1, i, 20+i);

    i=0;
    // lecture de l'eeprom BLOCK_0 et BLOCK_1 et mise dans le tableau array
    for(i=0; i<size ;i++)
        array[i] = DdiScaleI2cRead1Byte(ADDR_EEPROM_BLOCK_0,i);

    for(i=0; i<size ;i++)
        array1[i] = DdiScaleI2cRead1Byte(ADDR_EEPROM_BLOCK_1,i);

    i=0;

    for(i=0; i<size ;i++)
        array2[i] = 5;
    //don't write more than 16 bytes.
    i =  DdiScaleI2cWrite(ADDR_EEPROM_BLOCK_2, 0, array2, size);
    LOG("retour d'ecriture %d",i);

    memset(array2, 43, size);


    i=DdiScaleI2cRead(ADDR_EEPROM_BLOCK_2, 0, array2, size);
    LOG("retour de lecture %d",i);
}

void NOT_IN_LOOP_clearEeprom(uint8_t value)
{
    int8_t i=0x50;
    int16_t j=0;
    uint32_t cpt=0;
    for(i=ADDR_EEPROM; i<=ADDR_EEPROM_BLOCK_7 ;i++)
    {
        for(j=0; j<256 ;j++)
        {
            ExEEPROM_Write(i, j, 1, &value);
            cpt++;
            LOG("Erase Block %x | address %d | value %d [%d]",i,j,value,cpt);
        }
    }
}

void NIL_testExEepromRecover(void)
{
    uint8_t value=10;
    uint8_t add=10;
    ExEEPROM_Write(0, add, 1, &value);
    ExEEPROM_Write(1, add, 1, &value);
    value = 51; // simulation erreur 3 block non identique.
    ExEEPROM_Write(2, add, 1, &value);

    ExEEPROM_ReadCritic(0, add, 1, &value);
    LOG("Value = %d",value);
}

void exempleIO2Chenillard(uint8_t type, uint32_t delay)
{
    uint8_t i=0;

    switch (type) {
    case 1:
        //montée
        for(i=0;i<8;i++)
        {
            IOExp2.all = 0x03; //all led off

            if(i==0)
                IOExp2.bit.out_LD_BEAM1_SW4 = 0;
            else if(i==1)
                IOExp2.bit.out_LD_BEAM2_SW4 = 0;
            else
                IOExp2.all ^= 1<<i;

            updateIO2();
            sleep_ms(delay);
        }

        //descente
        for(i=7;i<=7;i--)
        {
            IOExp2.all = 0x03; //all led off

            if(i==0)
                IOExp2.bit.out_LD_BEAM1_SW4 = 0;
            else if(i==1)
                IOExp2.bit.out_LD_BEAM2_SW4 = 0;
            else
                IOExp2.all ^= 1<<i;

            updateIO2();
            sleep_ms(delay);
        }
        break;
    default:
        //montée
        for(i=0;i<8;i++)
        {
            IOExp2.all = 0x03; //all led off

            if(i==0)
                IOExp2.bit.out_LD_BEAM1_SW4 = 0;
            if(i==1)
                IOExp2.bit.out_LD_BEAM2_SW4 = 0;
            else
                IOExp2.all ^= 1<<i;

            updateIO2();
            sleep_ms(delay);
        }
        break;
    }
}

uint8_t checkButtonPressInt(void)
{
    uint8_t ret = 0xFF;
    ret = DdiScaleI2cRead1Byte(IOEXP_ADDR, PORT0_IN);
    ret = (~rxByte & 0x70);
    return ret;
}

BUTTON_TYPE checkButtonPress(void)
{
    uint8_t ret = 0x00;
    ret = DdiScaleI2cRead1Byte(IOEXP_ADDR, PORT0_IN);
    ret = ((~rxByte & 0x70) & 0xFF);
    return (BUTTON_TYPE)ret;
}

void configInterrupt(void)
{
    //Configure Pin PL2 for input
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);						
    GPIOPinTypeGPIOInput(GPIO_PORTL_BASE, GPIO_PIN_2);
    GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_2);

    //Configure Pin PL2 for IOExpender interruption.
    GPIOIntRegister(GPIO_PORTL_BASE, GPIOL_Handler);					// Fonctionne avec une fonction quelquonque qui n'est pas défini dans le .s ! ?
    GPIOIntTypeSet(GPIO_PORTL_BASE, GPIO_PIN_2, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTL_BASE, GPIO_PIN_2);
    //IntPrioritySet ( INT_GPIOL, 0xe0); 								// Not Needed
    IntEnable(INT_GPIOL);
}

void GPIOL_Handler()
{
    GPIOIntClear(GPIO_PORTL_BASE, GPIO_PIN_2);
    valueLed = checkButtonPressInt();   //lecture ne marche pas
}

void setGreenLed(bool v){

    value = (v)?0xBF:0xFF;
    DdiScaleI2cWrite1Byte(IOEXP_ADDR, PORT1_OUT, value);
}

void setRedLed(bool v){
    value = (v)?0xDF:0xFF;
    DdiScaleI2cWrite1Byte(IOEXP_ADDR, PORT1_OUT, value);
}

void setYellowLed(bool v){
    value = (v)?0xEF:0xFF;
    DdiScaleI2cWrite1Byte(IOEXP_ADDR, PORT1_OUT, value);
}

void setLed(uint8_t v){
    DdiScaleI2cWrite1Byte(IOEXP_ADDR, PORT1_OUT, value);
}

void exempleButtonPressInt(void)
{
    static uint8_t currentLed = 0xFF; //green on

    //currentLed = valueLed;
    currentLed ^= (0x40 | valueLed);

    valueLed = 0x00;

    setLed(currentLed);
    sleep_ms(250);

    currentLed ^= 0x40;
    setLed(currentLed);
    sleep_ms(250);
}

void exampleButtonPress()
{
    uint8_t v = (uint8_t)checkButtonPress();
    switch (v)
    {
    case PLUS_PRESSED:
        //Plus is pressed
        setGreenLed(1);
        break;

    case CAL_PRESSED:
        //CAL is pressed
        setGreenLed(0);
        setRedLed(0);
        setYellowLed(0);
        break;

    case PLUS_PRESSED|MINUS_PRESSED:
    //Plus is pressed
    setYellowLed(1);
    break;


    case MINUS_PRESSED:
        //MINUS is pressed
        setRedLed(1);
        break;

    case NO_BUTTON:
        //No button pressed
        break;

    default :
        break;
    }
}

void exampleChenillard(int type)
{
    switch (type)
    {
    case 1:
    {
        cpt=0;
        value = 0xE0;
        while(1)
        {
            sleep_ms(120);
            if(cpt==0)
            {
                value ^= (5<<4);
            }else if(cpt == 1)
            {
                value ^= (6<<4);
            }else if(cpt == 2){
                value ^= (3<<4);
            }else{
                value = 0x8F;
            }
            (cpt>=2)?cpt=0:cpt++;

            DdiScaleI2cWrite1Byte(IOEXP_ADDR, PORT1_OUT, value);
        }
        //break;
    }
    default:
    {
        cpt=0;
        value = 0xEF;
        while(1)
        {
            sleep_ms(500);
            if(cpt==0)
            {
                value ^= (5<<4);
            }else if(cpt == 1)
            {
                value ^= (6<<4);
            }else if(cpt == 2){
                value ^= (3<<4);
            }else{
                value = 0x8F;
            }
            (cpt>=2)?cpt=0:cpt++;

            DdiScaleI2cWrite1Byte(IOEXP_ADDR, PORT1_OUT, value);
        }
        //break;
    }
    }
}

void sleep_ms(uint32_t time)
{
    // SysCtlDelay(n) performs n loop.
    // For each loop, 3 instructions. Period for each loop = 3* (1/freq osc), 1 CLK per instruction
    // Temporization = 300000*(3*1/80MHz) = 11 ms
    SysCtlDelay(time*80000/3);
}

void sleep_s(uint32_t time)
{
    // SysCtlDelay(n) performs n loop.
    // For each loop, 3 instructions. Period for each loop = 3* (1/freq osc), 1 CLK per instruction
    // Temporization = 300000*(3*1/80MHz) = 11 ms
    SysCtlDelay(time*80*1e6/3);
}

void testVariableParameter(uint8_t num_of_args, ...)
{
    va_list vargs;
    int i=0;
    uint8_t arrayLocal[255];
    ASSERT(num_of_args < 255);
    memset(arrayLocal, 0, sizeof(arrayLocal));

    va_start(vargs,num_of_args);

    for(i=0;i<num_of_args;i++)
        arrayLocal[i] = va_arg(vargs,int);

    va_end(vargs);
}

