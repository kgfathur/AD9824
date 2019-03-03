/* 
  AD9824 LIBRARY - BASIC DEVICE TESTING EXAMPLE
  ----------------------------------------------
  
  */

#include "AD9824.h"

// Tentukan Alamat i2c dari AD9824.
// Kalau tidak tahu, silahkan lakukan scan otomatis
// dengan sample program dari internet untuk scan i2c devices
const byte DEV_ADDR = 0x48;                   // DEC: I2C address of the AD9824 (Change as needed)

AD9824 ad9824(DEV_ADDR);

// Contoh penggunaan clamp level
uint16_t clamp = 4;  // 0 - 1020 dengan 4 step (256 level)
                    // 0, 4, 8, 16 , .... 1016, 1020

void setup() {
  Serial.begin(115200);
  Wire.begin();
  while(!Serial);
  printDivider();
  Serial.print(F("\nAD9824 DEVICE TESTING\n"));    
  printDivider();
  Serial.print(F("\nINITIATING SERIAL COMMUNICATION\n"));  
  Serial.print(F("\nSerial Port is "));
  Serial.print(Serial ? "Open\n" : "Could not be opened\n"); 
  printDivider();
  ad9824.reset();
  quickDelay();
  Serial.print(F("\nINITIALIZING TESTS\n"));
  printDivider();
  ad9824.setGain(PXGA_GAIN0, 20);
  ad9824.setGain(PXGA_GAIN1, 30);
  ad9824.setGain(PXGA_GAIN2, 40);
  ad9824.setGain(PXGA_GAIN3, 50);
  printDivider();
  
  // CALMP_LEVEL = 0 - 1020 dengan step 4 (256 level)
  // 0, 4, 8, 16 , .... 1016, 1020
  // LIHAT SESUAI DATASHEET AD9824 HALAMAN 16
  ad9824.setClamp(128);
  printDivider();
  
  testPingDevice();
}
  
void loop() {}

void testPingDevice() {
  Serial.print(F("\nMencari perangkat... "));
  ad9824.ping() ? Serial.print(F("Tidak Ditemukan\n")) : Serial.print(F("Ditemukan!\n"));
  quickDelay();
}

void printDivider() {
  Serial.print(F("\n-------------------------------------\n"));
}

void quickDelay() {
  delay(50);
}
