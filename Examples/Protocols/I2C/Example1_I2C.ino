#include <Wire.h>

#define I2C_SDA 21
#define I2C_SCL 22

void setup()
{
  Wire.begin(I2C_SDA, I2C_SCL);
  Wire.beginTransmission(0x27);
  Wire.write("AA");
  Wire.endTransmission(true);
}

void loop()
{

}
