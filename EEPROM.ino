/*
 *  This sketch reads and writes wifi credentials from and to internal EEPROM
 *
 *  EEPROM
 *  At address = 0, length of ssid is stored
 *  At address = 1, length of password is stored
 *  From address 2, ssid is stored
 *  From address (2 + length(ssid)), password is stored
 *
 */

// LIBRARIES
#include "EEPROM.h"

// CONSTANTS
#define EEPROM_SIZE 64
String ssidC = "ESP32";
String passC = "toodlelab";

// VARIABLES
String ssidV, passV;  // Ssid & pass read from EEPROM are stored here

// FUNCTION DECLARATION
void readEEPROM();  // Reads ssid & pass from EEPROM
void writeEEPROM(); // Writes ssid & pass to EEPROM

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);

  writeEEPROM();
  readEEPROM();

  Serial.println("Reading from constants");
  Serial.println(ssidC);
  Serial.println(passC);

  Serial.println("Reading from EEPROM");
  Serial.println(ssidV);
  Serial.println(passV);
}

void loop() {
  // put your main code here, to run repeatedly:

}

// -------- READ WIFI SSID AND PASSWORD FROM EEPROM --------
void readEEPROM() {
  byte addrCounter = 0;  // Address counter
  byte ssidLen = byte(EEPROM.read(addrCounter++)); // Read ssid length
  byte passLen = byte(EEPROM.read(addrCounter++));  // Read pass length

  // Read Wifi SSID
  for (byte i = 0; i < ssidLen; i++) {
    ssidV += char(EEPROM.read(i + addrCounter));
    addrCounter++;
  }

  // Read Wifi Password
  for (byte i = 0; i < passLen; i++) {
    passV += char(EEPROM.read(i + addrCounter));
    addrCounter++;
  }
}

// -------- WRITE WIFI SSID AND PASSWORD TO EEPROM --------
void writeEEPROM() {
  byte addrCounter = 0;  // Address counter
  EEPROM.write(addrCounter++, ssidC.length());  // Store ssid length
  EEPROM.write(addrCounter++, passC.length());  // Store pass length

  // Write Wifi SSID
  for (byte i = 0; i < ssidC.length(); i++) {
    EEPROM.write(i + addrCounter, ssidC[i]);
    addrCounter++;
  }

  // Write Wifi Password
  for (byte i = 0; i < passC.length(); i++) {
    EEPROM.write(i + addrCounter, passC[i]);
    addrCounter++;
  }
}
