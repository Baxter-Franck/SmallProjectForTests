/**
 * @file ExEeprom_address.h
 * @details  This file regroup the addressing table of External Eeprom for OIML Scaling.\n
 * In this case used for merging SCB code into ICB.
 * Some of data are remove especially PPM already treated by ICB
 * @note NPD21806 Appendix A - EEPROM_Memory_Map_HR900 [AGILE]
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
/****************************************************************************/
/*             Memory locations in EEPROM. DEFINES                          */
/*              SFMEA<38.0> EEPROM memory defines                           */
/****************************************************************************/
#ifndef __EXEEPROM_ADDRESS_H__
#define __EXEEPROM_ADDRESS_H__

// address description                  Bank#,Subaddr,Length
#define WARM_BOOT                       0x00,0x00,0x02
//GAP
#define CAL_STS1_ADDR                   0x00,0x03,0x01
#define CAL_STS2_ADDR                   0x00,0x04,0x01
//GAP
#define GLOBAL_FLAG_ADDR                0x00,0x06,0x01
#define ZERO_POINT_THRESHOLD_ADDR       0x00,0x07,0x01
//GAP
#define DDIEPR_PPM_SUSPEND_STATE        0x00,0x08,0x01
#define DDIEPR_SPPMCONFIG               0x00,0x09,0x01
#define DDIEPR_PPMMODE                  0x00,0x0A,0x02
#define DDIEPR_PPM_SUSPEND_TIME         0x00,0x0C,0x02
//GAP
#define CAL_RHD1_ADDR                   0x00,0x10,0x04
#define CAL_LHD1_ADDR                   0x00,0x14,0x04
#define CAL_RFT1_ADDR                   0x00,0x18,0x04
#define CAL_LFT1_ADDR                   0x00,0x1C,0x04
//GAP
#define RESOLUTION_ADDR                 0x00,0x20,0x01
#define MAXWEIGHT_ADDR                  0x00,0x21,0x02
#define MINWEIGHT_ADDR                  0x00,0x23,0x02
#define MAXTILT_X_ADDR                  0x00,0x25,0x04
#define MAXTILT_Y_ADDR                  0x00,0x29,0x04
#define SCALECLASS_ADDR                 0x00,0x2D,0x01
//GAP
#define ACCEL_CALIBRATED_ADDR           0x00,0x2E,0x01
//GAP
#define CALLOCALLAT                     0x00,0x30,0x04 /* Local Latitude */
#define CALDESTLAT                      0x00,0x34,0x04 /* Dest. Latitude */
#define CALLOCALALT                     0x00,0x38,0x02 /* Local Altitude */
#define CALDESTALT                      0x00,0x3a,0x02 /* Dest Altitude  */
//GAP
#define DISP_ALS_ADDR                   0x00,0x3E,0x01
//GAP
#define GCIADJUSTWTADDR                 0x00,0x40,0x04
#define BOARDVERSIONNR_ADDR             0x00,0x44,0x04
#define ACC_CALIB_MIN_DUTY_CYCLE_ADDR   0x00,0x48,0x02
#define ACC_CALIB_MAX_DUTY_CYCLE_ADDR   0x00,0x4A,0x02
#define ACC_CALIB_MINDTYCYCL_DIFF_ADDR  0x00,0x4C,0x02
#define ACC_CALIB_MAXDTYCYCL_DIFF_ADDR  0x00,0x4E,0x02
#define DDIEPR_PPMOOBWEIGHT             0x00,0x50,0x04
#define DDIEPR_PPMMAXWEIGHT             0x00,0x54,0x04
#define DDIEPR_PPMMINWEIGHT             0x00,0x58,0x04
//GAP
#define AVGBEAMCONSTANT_ADDR            0x00,0x5C,0x04

#define TARE_RHD_ADDR                   0x00,0x60,0x04
#define TARE_LHD_ADDR                   0x00,0x64,0x04
#define TARE_RFT_ADDR                   0x00,0x68,0x04
#define TARE_LFT_ADDR                   0x00,0x6C,0x04

#define SCALE_TYPE_ADDR                 0x00,0x70,0x01
#define SCALE_TEST_ADDR                 0x00,0x71,0x01

#define SCALE_SERIAL_NUMBER_ADDR        0x00,0x72,0x04

#define CALXSHIFTPER_G                  0x00,0x76,0x04
#define CALXAT0G                        0x00,0x7a,0x04
#define CALYSHIFTPER_G                  0x00,0x80,0x04
#define CALYAT0G                        0x00,0x84,0x04

#define X_OFFSET_ADDR                   0x00,0x88,0x04
#define Y_OFFSET_ADDR                   0x00,0x8C,0x04

#define FACTORYOFSTLFT1ADDR             0x00,0x90,0x04
#define FACTORYOFSTRFT1ADDR             0x00,0x94,0x04
#define FACTORYOFSTRHD1ADDR             0x00,0x98,0x04
#define FACTORYOFSTLHD1ADDR             0x00,0x9C,0x04

#define LOCALGRAVITYADDR                0x00,0xA0,0x04
#define DESTGRAVITYADDR                 0x00,0xA4,0x04
#define POSALLOWED_0_SHIFTADDR          0x00,0xA8,0x01
#define NEGALLOWED_0_SHIFTADDR          0x00,0xA9,0x01
//GAP
#define ZEROSHIFTLFTADDR                0x00,0xb0,0x04
#define ZEROSHIFTRFTADDR                0x00,0xb4,0x04
#define ZEROSHIFTRHDADDR                0x00,0xb8,0x04
#define ZEROSHIFTLHDADDR                0x00,0xbc,0x04

#define DIAGHIST                        0x00,0xC0,0x04
#define DIAGPERMHIST                    0x00,0xC4,0x04
#define DIAGRECOCC                      0x00,0xC8,0x02 //This takes up 20 Bytes ie from C8 till DC
//GAP
#define DDIEPR_PPMAUTOZERO_LH           0x00,0xE0,0x04
#define DDIEPR_PPMAUTOZERO_LF           0x00,0xE4,0x04
#define DDIEPR_PPMAUTOZERO_RH           0x00,0xE8,0x04
#define DDIEPR_PPMAUTOZERO_RF           0x00,0xEC,0x04

#define DDIEPR_PPMWTDURINGARMING_LH     0x00,0xF0,0x04
#define DDIEPR_PPMWTDURINGARMING_LF     0x00,0xF4,0x04
#define DDIEPR_PPMWTDURINGARMING_RF     0x00,0xF8,0x04
#define DDIEPR_PPMWTDURINGARMING_RH     0x00,0xFC,0x04

#endif
