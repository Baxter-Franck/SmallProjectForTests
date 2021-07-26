#ifndef __IOEXP2_H__
#define __IOEXP2_H__

#include "ddi_I2C.h"

#define IOEXP2_ADDR 0x77

// Doc IOExpender
#define TCA9535_INPUT_REG0      0x00        // Input status register
#define TCA9535_INPUT_REG1      0x01        // Input status register
#define TCA9535_OUTPUT_REG0     0x02        // Output register to change state of output BIT set to 1, output set HIGH
#define TCA9535_OUTPUT_REG1     0x03        // Output register to change state of output BIT set to 1, output set HIGH
#define TCA9535_POLARITY_REG0   0x04        // Polarity inversion register. BIT '1' inverts input polarity of register 0x00
#define TCA9535_POLARITY_REG1   0x05        // Polarity inversion register. BIT '1' inverts input polarity of register 0x00
#define TCA9535_CONFIG_REG0     0x06        // Configuration register. BIT = '1' sets port to input BIT = '0' sets port to output
#define TCA9535_CONFIG_REG1     0x07        // Configuration register. BIT = '1' sets port to input BIT = '0' sets port to output

struct TCA9535_sBit{
    uint8_t B0:1;
    uint8_t B1:1;
    uint8_t B2:1;
    uint8_t B3:1;
    uint8_t B4:1;
    uint8_t B5:1;
    uint8_t B6:1;
    uint8_t B7:1;
};

union TCA9535_uPort{
    uint8_t all;
    struct TCA9535_sBit bit;
};

struct TCA9535_sPorts{
    union TCA9535_uPort P0;
    union TCA9535_uPort P1;
};

union TCA9535{
    uint16_t all;
    struct TCA9535_sPorts ports;
};

typedef struct{
    union TCA9535 Input;
    union TCA9535 Output;
    union TCA9535 PolarityInversion;
    union TCA9535 Config;
}TCA9535_t;

extern TCA9535_t tca9535;

void configIO2(void);
void updateIO2(void);


#endif // __IOEXP2_H__
