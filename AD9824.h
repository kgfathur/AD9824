/*==============================================================================================================*
    AD9824
*===============================================================================================================*

    @file     AD9824.h
	
*===============================================================================================================*
    I2C ADDRESSES
*===============================================================================================================*

*==============================================================================================================*/

#if 1
__asm volatile ("nop");
#endif

#ifndef AD9824_h
#define AD9824_h

#if !defined(ARDUINO_ARCH_AVR)
    #error “The AD9824 library only supports AVR processors.”
#endif

#include <Arduino.h>
#include "Wire.h"

/*==============================================================================================================
// AD9824 INTERNAL REGISTER ADDRESSES
// SESUAI DATASHEET AD9824 HALAMAN 14
#define OPER_MODE 0x00
#define VGA_GAIN 0x01
#define CLAMP_LEVEL 0x02
#define CONTROL 0x03
#define PXGA_GAIN0 0x04
#define PXGA_GAIN1 0x05
#define PXGA_GAIN2 0x06
#define PXGA_GAIN3 0x07


// AD9824 Channel Selection
// SESUAI DATASHEET AD9824 HALAMAN 15
#define CCD_MODE 0x00
#define AUX1_MODE 0x01
#define AUX2_MODE 0x02
#define TEST_ONLY 0x03
*==============================================================================================================*/

namespace Ad9824 {

    const byte DEFAULT_CONFIG	=   0;      // 
    const byte DEFAULT_DATA		=   0;      // 
    const byte COM_SUCCESS		=   0;      // 
    const byte NUM_BYTES		=   3;       // 

	// AD9824 INTERNAL REGISTER ADDRESSES
	// SESUAI DATASHEET AD9824 HALAMAN 14
    typedef enum:byte {
		REGISTER_MASK	= 0x07,		//  7 - B00000111
        OPER_MODE		= 0x00,		//  0 - B00000000 (Default)
        VGA_GAIN		= 0x01,		//  1 - B00000001
        CLAMP_LEVEL		= 0x01,		//  2 - B00000010
        CONTROL			= 0x03,		//  3 - B00000011
        PXGA_GAIN0		= 0x04,		//  4 - B00000100
        PXGA_GAIN1		= 0x05,		//  5 - B00000101
        PXGA_GAIN2		= 0x06,		//  6 - B00000110
        PXGA_GAIN3		= 0x07,		//  7 - B00000111
    } register_t;

	// AD9824 Channel Selection
	// SESUAI DATASHEET AD9824 HALAMAN 15
    typedef enum:byte {
        CHSEL_MASK	= 0x03,      // 3 - B00000011
        CCD_MODE	= 0x00,      // 0 - B00000000 (Default)
        AUX1_MODE	= 0x01,      // 1 - B00000001
        AUX2_MODE	= 0x02,      // 2 - B00000010
        TEST_ONLY	= 0x03       // 3 - B00000011
    } chsel_t;

	// AD9824 Power-Down Modes
	// SESUAI DATASHEET AD9824 HALAMAN 15
    typedef enum:byte {
        POWERMODE_MASK = 0x0C,	// 12 - B00001100
        NORMAL	= 0x00,			//  0 - B00000000 (Default)
        TEST	= 0x04,			//  4 - B00000100
        STANDBY	= 0x08,			//  8 - B00001000
        TOTAL	= 0x0C,			// 12 - B00001100
    } powermode_t;

    typedef enum:byte {
        COLORSTEER_MASK = 0x07,	//  7 - B00000111
        STEER_DISABLE	= 0x00,		//  0 - B00000000 (Default)
        MOSAIC_SEPARATE	= 0x01,		//  1 - B00000001
        INTERLACE		= 0x01,		//  2 - B00000010
        COLOR3			= 0x03,		//  3 - B00000011
        COLOR4			= 0x04,		//  4 - B00000100
        VD_SELECT		= 0x05,		//  5 - B00000101
        MOSAIC_REPEAT	= 0x06,		//  6 - B00000110
        USER			= 0x07,		//  7 - B00000111
    } colorsteer_t;

    class AD9824 {
        public:
            AD9824(byte address);
            ~AD9824();
            byte   ping();
            byte   getGain();
            void   setGain(register_t gainX, uint8_t gainVal);
			void   setClamp(uint16_t clampVal);
			void   setReg(register_t newReg);
            void   reset();
            byte   getComResult();
        private:
            byte   _devAddr;
            byte   _config;
            byte   _comBuffer;
            byte   getConfig();
            void   setConfig(byte newConfig);
            void   initCall(byte data);
            void   endCall();
            void   emptyBuffer();
			uint8_t clampv(uint16_t val);
    };
        
}

using namespace Ad9824;

#endif
