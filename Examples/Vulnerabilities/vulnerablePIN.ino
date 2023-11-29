// Requies keypad libary by Mark Stanly and Alexander Brevig

#include <Keypad.h>
#include "esp_clk.h"

#define ROW_NUM 4
#define COLUMN_NUM 4
#define TRIGGER_LED 21
#define RED_LED 22
#define GREEN_LED 23

const char *PASSWORD = "2580";
char input_password[32];
int charCounter = 0;
int debugDelay = 0;
unsigned long timeStart;
unsigned long timeStop;

char keys[ROW_NUM][COLUMN_NUM] = {{'1','2','3', 'A'},{'4','5','6', 'B'},{'7','8','9', 'C'},{'*','0','#', 'D'}};
byte pin_rows[ROW_NUM] = {26, 27, 14, 12}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {17, 15, 4, 2}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(TRIGGER_LED, OUTPUT);
  uint32_t cpu_freq = esp_clk_cpu_freq();
  Serial.begin(115200);
  Serial.println("Starting application, running on an ESP32 with CPU frequency of: " + String(cpu_freq) + "hz");
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
