/*==============================================================================================================*
    AD9824
*===============================================================================================================*

    @file     AD9824.h
 
*==============================================================================================================*/

#if 1
__asm volatile ("nop");
#endif

#include "AD9824.h"

/*==============================================================================================================*
    CONSTRUCTOR
 *==============================================================================================================*/

AD9824::AD9824(byte devAddr) {
    _devAddr   = devAddr;
    _config    = DEFAULT_CONFIG;
    _comBuffer = COM_SUCCESS;
}

/*==============================================================================================================*
    DESTRUCTOR
 *==============================================================================================================*/

AD9824::~AD9824() {}

/*==============================================================================================================*
    PING (0 = SUCCESS / 1-7 = I2C ERROR CODE)
 *==============================================================================================================*/

byte AD9824::ping() {
    Wire.beginTransmission(_devAddr);
    return Wire.endTransmission();
}

/*==============================================================================================================*
    GET GAIN
 *==============================================================================================================*/

byte AD9824::getGain() {
    return (1 << (_config & REGISTER_MASK));
}

/*==============================================================================================================*
    SET GAIN
 *==============================================================================================================*/

void AD9824::setGain(register_t gainX, uint8_t gainVal) {
    setConfig((_config & ~REGISTER_MASK) | (gainX & REGISTER_MASK));
	Wire.write(gainVal);
}

/*==============================================================================================================*
    SET CLAMP LEVEL
 *==============================================================================================================*/

void AD9824::setClamp(uint16_t clampVal) {
    setReg(CLAMP_LEVEL);
	Wire.write(clampv(clampVal));
}

/*==============================================================================================================*
    SET REGISTER
 *==============================================================================================================*/

void AD9824::setReg(register_t newReg) {
    setConfig((_config & ~REGISTER_MASK) | (newReg & REGISTER_MASK));
}

/*==============================================================================================================*
// RESET
 *==============================================================================================================*/

void AD9824::reset() {
    setConfig(DEFAULT_CONFIG);
}

/*==============================================================================================================*
    GET COMMUNICATION RESULT
 *==============================================================================================================*/

byte AD9824::getComResult() {
    return _comBuffer;
}

/*==============================================================================================================*
    GET CONFIGURATION SETTINGS (FROM DEVICE)
 *==============================================================================================================*/

byte AD9824::getConfig() {
    byte devConfig;
    Wire.requestFrom(_devAddr, NUM_BYTES);              // request 3 bytes from device
    if (Wire.available() == NUM_BYTES) {                // if 3 bytes were recieved...
        for (byte i=2; i>0; i--) Wire.read();           // skip data register bytes
        devConfig = Wire.read();                        // store device config byte
    } else {                                            // if 3 bytes were not recieved...
        emptyBuffer();                                  // empty I2C buffer
        _comBuffer = ping();                            // store I2C error code to find out what went wrong
    }
    return devConfig;                                   // return device config byte
}

/*==============================================================================================================*
    SET CONFIGURATION REGISTER
 *==============================================================================================================*/

void AD9824::setConfig(byte newConfig) {
    initCall(newConfig);
    endCall();
    if (_comBuffer == COM_SUCCESS) _config = newConfig;
}

/*==============================================================================================================*
    INITIATE I2C COMMUNICATION
 *==============================================================================================================*/

void AD9824::initCall(byte data) {
    Wire.beginTransmission(_devAddr);
    Wire.write(data);
}

/*==============================================================================================================*
    END I2C COMMUNICATION
 *==============================================================================================================*/

void AD9824::endCall() {
    _comBuffer = Wire.endTransmission();
}

/*==============================================================================================================*
    EMPTY I2C BUFFER
 *==============================================================================================================*/

void AD9824::emptyBuffer() {
    while (Wire.available()) Wire.read();
}

uint8_t AD9824::clampv(uint16_t val) {
//  Serial.print("val:");
//  Serial.print(val);
  val = val / 4;
//  Serial.print(" -> ");
//  Serial.println(val);
  return (uint8_t)val;
}