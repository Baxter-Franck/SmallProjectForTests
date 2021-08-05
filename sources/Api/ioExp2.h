#ifndef __IOEXP2_H__
#define __IOEXP2_H__

#include "ddi_scale_i2c.h"

#define IOEXP_DEMO_BOARD
#ifdef IOEXP_DEMO_BOARD
#define ADDR_IO_EXP_2 0x77                    //IO2 on demo board !! no correct address on Accella
#else
#define ADDR_IO_EXP_2 0x26                    //IO2 on real board/bed Accella
#endif

// Doc IOExpender
#define TCA9535_INPUT_REG0      0x00        // Input status register
#define TCA9535_INPUT_REG1      0x01        // Input status register
#define TCA9535_OUTPUT_REG0     0x02        // Output register to change state of output BIT set to 1, output set HIGH
#define TCA9535_OUTPUT_REG1     0x03        // Output register to change state of output BIT set to 1, output set HIGH
#define TCA9535_POLARITY_REG0   0x04        // Polarity inversion register. BIT '1' inverts input polarity of register 0x00
#define TCA9535_POLARITY_REG1   0x05        // Polarity inversion register. BIT '1' inverts input polarity of register 0x00
#define TCA9535_CONFIG_REG0     0x06        // Configuration register. BIT = '1' sets port to input BIT = '0' sets port to output
#define TCA9535_CONFIG_REG1     0x07        // Configuration register. BIT = '1' sets port to input BIT = '0' sets port to output


struct TCA9535_Bits
{
    uint8_t out_LD_BEAM1_SW4 : 1,
            out_LD_BEAM2_SW4 : 1,
            out_LD_BEAM3_SW4 : 1,
            out_LD_BEAM4_SW4: 1,
            out_LED_DIAG_YEL : 1,
            out_LED_DIAG_GRN : 1,
            out_LED_DIAG_RED : 1,
            in_INT_ACCELERO : 1;
    uint8_t out_NC_NORMALLY_OPENED : 1,
            out_NC_NORMALLY_CLOSED : 1,
            out_PC_NORMALLY_OPENED : 1,
            out_PC_NORMALLY_CLOSED : 1,
            unused : 4;
};

typedef union
{
    uint16_t all;
    struct TCA9535_Bits bit;
}IOExp2_Data_t;

extern IOExp2_Data_t IOExp2;

void configIOExp2(void);
uint8_t ioExp2Write(uint8_t address, IOExp2_Data_t data);
void updateIO2(void);


#endif // __IOEXP2_H__
