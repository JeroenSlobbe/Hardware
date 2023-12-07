#include <Wire.h>
#define eeprom 0x50 //defines the base address of the EEPROM
#define I2C_SDA 21
#define I2C_SCL 22

void setup() {
  Wire.begin(I2C_SDA, I2C_SCL);
  Serial.begin(112600);
  //writePINToEEPROM(eeprom,1,"1234");
  //Serial.println(readEEPROMPIN(eeprom,1,4));
  //dumpEEPROM(eeprom,65536);
}

void loop() {
  // put your main code here, to run repeatedly:

}


void dumpEEPROM(int deviceaddress, int EEPROMSize)
{
  for(int address = 0; address< EEPROMSize; address++) 
  {
    Serial.print(readEEPROM(deviceaddress, address), HEX);
    Serial.print(" ");
    if(address % 8 == 0)
    {
      Serial.println(""); 
    }
  }  
}

void writePINToEEPROM(int deviceaddress, unsigned int eeaddress, String PIN)
{
  char PINArray[PIN.length() +1];
  PIN.toCharArray(PINArray, PIN.length() + 1);
  for(int i = 0; i < sizeof(PINArray); i++)
  {
    writeEEPROM(deviceaddress, eeaddress + i, PINArray[i]);
  }
}

int readEEPROMPIN(int deviceaddress, unsigned int eeaddress, int PINLength ) {
  char dataFromEEPROM[(PINLength)];
  for (unsigned int i = 0; i < sizeof(dataFromEEPROM); i++)
  {
    dataFromEEPROM[i] = readEEPROM(deviceaddress, (eeaddress + i));
    Serial.println("Reading: " + String(eeaddress + i) + " value: " + dataFromEEPROM[i]);
  }
  return(atoi(dataFromEEPROM));
}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, byte data ) {
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));      //writes the MSB
  Wire.write((int)(eeaddress & 0xFF));    //writes the LSB
  Wire.write(data);
  Wire.endTransmission();
  delay(5); //required as this is the maximum time to complete the write cycle
}

byte readEEPROM(int deviceaddress, unsigned int eeaddress ) {
  byte rdata = 0xFF;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8));      //writes the MSB (>> is the right shift operator, shifting eeadress bytes with 8 positions to the right)
  Wire.write((int)(eeaddress & 0xFF));    //writes the LSB (& is the bitwise AND operator)
  Wire.endTransmission();
  Wire.requestFrom(deviceaddress,1);
  if (Wire.available()) 
    rdata = Wire.read();
  return rdata;
}

