// Requies keypad libary by Mark Stanly and Alexander Brevig

#include <Keypad.h>
#include "esp_clk.h"
#include <Wire.h>

#define eeprom 0x50 //defines the base address of the EEPROM
#define I2C_SDA 4
#define I2C_SCL 2

#define ROW_NUM 4
#define COLUMN_NUM 4
#define TRIGGER_LED 15
#define RED_LED 22
#define GREEN_LED 23

//const char *PASSWORD = "2580";
char PASSWORD[4];
char input_password[32];
int charCounter = 0;
int debugDelay = 0;
unsigned long timeStart;
unsigned long timeStop;

char keys[ROW_NUM][COLUMN_NUM] = {{'1','2','3', 'A'},{'4','5','6', 'B'},{'7','8','9', 'C'},{'*','0','#', 'D'}};
byte pin_rows[ROW_NUM] = {13, 12, 14, 27}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {26, 25, 33, 32}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Wire.begin(I2C_SDA, I2C_SCL);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(TRIGGER_LED, OUTPUT);
  digitalWrite(TRIGGER_LED, LOW); //By default PIN 15 is HIGH, its the ESP32 pin that hides the boot message. Making it low, shows the boot message again and ensures normal working.
  uint32_t cpu_freq = esp_clk_cpu_freq();
  Serial.begin(115200);
  Serial.println("Starting application, running on an ESP32 with CPU frequency of: " + String(cpu_freq) + "hz");
  readEEPROMPIN(eeprom,1);
  Serial.println("Obtaining password from external EEPROM: " + String(PASSWORD));
}

void blinkRED()
{
  digitalWrite(RED_LED, HIGH);
  delay(1000);
  digitalWrite(RED_LED, LOW);   
}

void blinkGREEN()
{
  digitalWrite(GREEN_LED, HIGH);
  delay(1000);
  digitalWrite(GREEN_LED, LOW);   
}

void resetPINBuffer()
{
  int i;
  for(i=0; i< charCounter; i++)
  {
    input_password[i] = '\0';
  }
  charCounter = 0;  
}

int vulnerableCheckPassword()
{
  int i;
  
  for(i=0; i< sizeof(PASSWORD);i++)
  {
    delay(debugDelay);
    if(input_password[i] != PASSWORD[i])
    {
      return 0;
    }
  }
  Serial.println("Password correct"); //needed to cause a delay when the final digit is also correct. Normally a shell would pop :)
  return 1;
}

void loop()
{
  char key = keypad.getKey();
  int result;
  
  if(key)
  {
    if((key == '#' or charCounter > 4))
    {
      Serial.println("Checking PIN: " + String(input_password));
      timeStart = micros();
      Serial.println("Timestamp before password check: " + String(timeStart));
      digitalWrite(TRIGGER_LED, HIGH);
      result = vulnerableCheckPassword();
      digitalWrite(TRIGGER_LED, LOW);
      timeStop = micros();
      Serial.println("Timestamp after password check: " + String(timeStop) + " password check took: " + String(timeStop - timeStart) + " us");
      
      resetPINBuffer();
      if(result)
      {
        blinkGREEN();
      }
      else
      {
        blinkRED();
      }
    }
    else
    {
      input_password[charCounter] = key;
      charCounter = charCounter + 1;
    }
  }    
}

void readEEPROMPIN(int deviceaddress, unsigned int eeaddress) {
  for (unsigned int i = 0; i < sizeof(PASSWORD); i++)
  {
    PASSWORD[i] = readEEPROM(deviceaddress, (eeaddress + i));
  }
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
