#ifndef __DEFINE_HR_H__
#define __DEFINE_HR_H__

#include <stdbool.h>
#include <stdint.h>

#define MAX_HIB_NUM		2

#define DEFAULT_CONFIG 		0x000
#define HR900_PLUS 			0x000
#define ACCELLA_MOINS 		0x001
#define ACCELLA_DEUX 		0x010
#define ACCELLA_PLUS 		0x011
#define V100 00
#define V120 01
#define V230 02

#define FRENCH 0x000100

#define BIT0_MASK			(0x01)
#define BIT1_MASK			(0x02)
#define BIT2_MASK			(0x04)
#define BIT3_MASK			(0x08)
#define BIT4_MASK			(0x10)
#define BIT5_MASK			(0x20)

#define FALSE				(0x0)
#define TRUE				(0x1)

#define ZERO				(0)
#define ONE					(1)
#define TWO					(2)
#define THREE				(3)
#define FOUR				(4)
#define FIVE				(5)
#define SIX 				(6)
#define SEVEN				(7)
#define EIGHT				(8)
#define NINE				(9)
#define TEN 				(10)
#define ELEVEN				(11)
#define TWELVE				(12)
#define THIRTEEN			(13)
#define FOURTEEN 			(14)
#define FIFTEEN 			(15)
#define ONE_HUNDRED			(100)


#define RETURN_NOK_BAD_PARAM	(-2)
#define RETURN_NOK				(-1)
#define RETURN_OK				(0)


#define XTAL_FREQ				(16000000)
#define PROC_FREQ				(XTAL_FREQ*FIVE) //See main.c: SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

#define ICB_BOARD_NODE_ID		(0x02)
#define SCB_BOARD_NODE_ID		(0x09)
#define HIB_BOARD_NODE_ID		(0x04)
#define HIB2_BOARD_NODE_ID		(0x05)
#define MCB_BOARD_NODE_ID		(0x0A)
#define WAM_BOARD_NODE_ID		(0x06)


// Angle Tools
#define PI_CONSTANT				(3.141592)
#define DEGREE_180				(180)
#define DEGREE2RADIAN(x)		((x*PI_CONSTANT)/DEGREE_180)

////////////////////////////////////////////////////////////////////////////////
///< tare led blink frequency = ( 1 / ( task duration * 2 ) ) / DIVIDER
///< task duration : 100 ms -> frq = 5hz / DIVIDER
///< need to be different to 0
#define HIGH_PRIORITY_DIVIDER_100MS 		2   ///< 2.5 Hz
#define MIDDLE_PRIORITY_DIVIDER_100MS 		7  	///< 0.7 Hz
#define LOW_PRIORITY_DIVIDER_100MS 			12  ///< 0.4 Hz

/*
*			Types for CANOpen stack compatibility
*/
typedef unsigned    char    UNSIGNED8;
typedef unsigned    short   UNSIGNED16;
typedef unsigned    long    UNSIGNED32;
typedef signed      short   INTEGER16;
typedef signed      long    INTEGER32;
typedef float 				FLOAT32_T;



typedef unsigned    char   BOOLEAN;                  /*!<  1 bit  basic type */
typedef unsigned    char   BYTE;                     /*!<  8 bits basic type */
typedef unsigned    short  WORD;                    /*!< 16 bits basic type */
typedef unsigned    long   DWORD;                    /*!< 32 bits basic type */


typedef    union
{
    UNSIGNED32 data32;
    UNSIGNED16 data16[2];
    UNSIGNED8  data8[4];
}data_t;

/// Defines   CPU status register size
typedef unsigned int        CPU_SR;
#define OS_CPU_SR UNSIGNED32
#define OS_ENTER_CRITICAL() {IntMasterDisable();cpu_sr=cpu_sr;}
#define OS_EXIT_CRITICAL()  {IntMasterEnable();}





// =================================================
// Defines for global plateform compatibility
// =================================================
/// 1 byte
typedef unsigned char       BOOLEAN_T;
/// 8-bit unsigned
typedef unsigned char       UNSIGNED8_T;
/// 16-bit unsigned
typedef unsigned short int  UNSIGNED16_T;
/// 32-bit unsigned
typedef unsigned int        UNSIGNED32_T;

/// 8-bit signed
typedef signed   char       SIGNED8_T;
/// 16-bit signed
typedef signed   short int  SIGNED16_T;
/// 32-bit signed
typedef signed   int        SIGNED32_T;

/// Byte wide bit fields
typedef unsigned char       BIT_FIELD8_T;
/// Half Word length bit fields
typedef unsigned short int  BIT_FIELD16_T;
/// Word length bit fields
typedef UNSIGNED32_T        BIT_FIELD32_T;
/// String pointer
typedef char *              STRING_T;
/// float type
typedef  float              FLOAT_T;
/// float type
typedef  float              float32_t;
//double type
typedef  double             float64_t;
//character type
typedef char                char8_t;


/// \typedef Emulates a C++ string data type using a char pointer.
//typedef char*                                      STRING_T;
/// \def Emulates a public function in C by making the function automatic.
#define PUBLIC
/// \def Emulates an internal function in C by making the function automatic.
#define INTERNAL
/// \def Emulates a private function in C by making the function static.
#define PRIVATE                                    static




/// \def SHIFT_CNT_0: Shift by 0 bits
#define SHIFT_CNT_0	       ((UNSIGNED8_T)(0))
/// \def SHIFT_CNT_1: Shift by 1 bits
#define SHIFT_CNT_1	       ((UNSIGNED8_T)(1))
/// \def SHIFT_CNT_2: Shift by 2 bits
#define SHIFT_CNT_2	       ((UNSIGNED8_T)(2))
/// \def SHIFT_CNT_3: Shift by 3 bits
#define SHIFT_CNT_3	       ((UNSIGNED8_T)(3))
/// \def SHIFT_CNT_4: Shift by 4 bits
#define SHIFT_CNT_4	       ((UNSIGNED8_T)(4))
/// \def SHIFT_CNT_5: Shift by 5 bits
#define SHIFT_CNT_5	       ((UNSIGNED8_T)(5))
/// \def SHIFT_CNT_6: Shift by 6 bits
#define SHIFT_CNT_6	       ((UNSIGNED8_T)(6))
/// \def SHIFT_CNT_7: Shift by 7 bits
#define SHIFT_CNT_7	       ((UNSIGNED8_T)(7))
/// \def SHIFT_CNT_8: Shift by 8 bits
#define SHIFT_CNT_8	       ((UNSIGNED8_T)(8))
/// \def SHIFT_CNT_9: Shift by 9 bits
#define SHIFT_CNT_9	       ((UNSIGNED8_T)(9))
/// \def SHIFT_CNT_10: Shift by 10 bits
#define SHIFT_CNT_10       ((UNSIGNED8_T)(10))
/// \def SHIFT_CNT_11: Shift by 11 bits
#define SHIFT_CNT_11       ((UNSIGNED8_T)(11))
/// \def SHIFT_CNT_12: Shift by 12 bits
#define SHIFT_CNT_12       ((UNSIGNED8_T)(12))
/// \def SHIFT_CNT_13: Shift by 13 bits
#define SHIFT_CNT_13       ((UNSIGNED8_T)(13))
/// \def SHIFT_CNT_14: Shift by 14 bits
#define SHIFT_CNT_14       ((UNSIGNED8_T)(14))
/// \def SHIFT_CNT_15: Shift by 15 bits
#define SHIFT_CNT_15       ((UNSIGNED8_T)(15))
/// \def SHIFT_CNT_16: Shift by 16 bits
#define SHIFT_CNT_16       ((UNSIGNED8_T)(16))
/// \def SHIFT_CNT_17: Shift by 17 bits
#define SHIFT_CNT_17       ((UNSIGNED8_T)(17))
/// \def SHIFT_CNT_18: Shift by 18 bits
#define SHIFT_CNT_18       ((UNSIGNED8_T)(18))
/// \def SHIFT_CNT_19: Shift by 19 bits
#define SHIFT_CNT_19       ((UNSIGNED8_T)(19))
/// \def SHIFT_CNT_20: Shift by 20 bits
#define SHIFT_CNT_20       ((UNSIGNED8_T)(20))
/// \def SHIFT_CNT_21: Shift by 21 bits
#define SHIFT_CNT_21       ((UNSIGNED8_T)(21))
/// \def SHIFT_CNT_22: Shift by 22 bits
#define SHIFT_CNT_22       ((UNSIGNED8_T)(22))
/// \def SHIFT_CNT_23: Shift by 23 bits
#define SHIFT_CNT_23       ((UNSIGNED8_T)(23))
/// \def SHIFT_CNT_24: Shift by 24 bits
#define SHIFT_CNT_24       ((UNSIGNED8_T)(24))
/// \def SHIFT_CNT_25: Shift by 25 bits
#define SHIFT_CNT_25       ((UNSIGNED8_T)(25))
/// \def SHIFT_CNT_26: Shift by 26 bits
#define SHIFT_CNT_26       ((UNSIGNED8_T)(26))
/// \def SHIFT_CNT_27: Shift by 27 bits
#define SHIFT_CNT_27       ((UNSIGNED8_T)(27))
/// \def SHIFT_CNT_28: Shift by 28 bits
#define SHIFT_CNT_28       ((UNSIGNED8_T)(28))
/// \def SHIFT_CNT_29: Shift by 29 bits
#define SHIFT_CNT_29       ((UNSIGNED8_T)(29))
/// \def SHIFT_CNT_30: Shift by 30 bits
#define SHIFT_CNT_30       ((UNSIGNED8_T)(30))
/// \def SHIFT_CNT_31: Shift by 31 bits
#define SHIFT_CNT_31       ((UNSIGNED8_T)(31))
/// \def SHIFT_CNT_31: Shift by 31 bits
#define SHIFT_CNT_32       ((UNSIGNED8_T)(32))







/// \def absolute variable location, ignores any +First and +Last Constraints
#define __at(_addr) __attribute__ ((at(_addr)))


#define BIT(x)             (1 << (x))
#define SETBIT(addr,x)     ((addr) |= BIT(x))
#define CLEARBIT(addr,x)   ((addr) &= ~BIT(x))
#define BITSET(addr,x)     (((addr) & BIT(x)) == BIT(x))
#define BITCLEARED(addr,x) (((addr) & BIT(x)) == 0)
/********************************************************************************/


/***************************************************
*  Global variables Section
***************************************************/
extern uint32_t HR_Sys_Clock_Freq;		//The actual configured system clock frequency in Hz via SysCtlClockFreqSet()
extern volatile uint32_t sysTickCounter_1s;
extern volatile uint32_t sysTickCounter_1ms;
extern volatile uint32_t sysTickCounter_10ms;
extern volatile uint32_t sysTickCounter_50ms;
extern volatile uint32_t sysTickCounter_100ms;

extern unsigned short volatile gTimCnt;

extern volatile uint64_t sysTickCounter_1ms_timer1;								/*1 miliseconds tick counter used for timer 1*/
extern volatile uint64_t sysTickCounter_1ms_timer2;								/*1 miliseconds tick counter used for timer 2*/


#endif
