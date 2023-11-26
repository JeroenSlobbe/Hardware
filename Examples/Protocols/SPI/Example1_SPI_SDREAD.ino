#include "FS.h"
#include "SD.h"   //Note this libary works with FAT32, it fails for ext.FAT32
#include "SPI.h"
#include <Wire.h>

#define SPI_CS 17
#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23

SPIClass spi = SPIClass(VSPI);

unsigned char buffer[512];
File myFile;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Settup");

  spi.begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_CS);
  spi.setDataMode(SPI_MODE0);
  spi.setBitOrder(MSBFIRST);

    if(!SD.begin(SPI_CS,spi)){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    } 

    Serial.println(readFile(SD, "/AAAAAAAAAAAA.txt"));
    Serial.println(readFile(SD, "/EEEEEE.txt"));
    Serial.println(readFile(SD, "/EEEEEF.txt"));
    Serial.println(readFile(SD, "/FEEEEE.txt"));
    Serial.println(readFile(SD, "/AAAAAAAAAAAA.txt"));
}

void loop() {
  // put your main code here, to run repeatedly:

}


String readFile(fs::FS &fs, const char * path)
{
  String fileContent;
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if(!file){
    Serial.println("Failed to open file for reading");
    return "Error reading file";
  }
  Serial.print("Read from file: ");
  while(file.available())
  {
    char c = file.read();
    fileContent.concat(c);
    //Serial.write(file.read());
  }
  file.close();
  return fileContent;
}
