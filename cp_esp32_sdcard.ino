
#include "public.h"
#include <SPI.h>
#include <SD.h>

#define CPIOT_SS_PIN 5
#define CPIOT_MOSI_PIN 23
#define CPIOT_SCK_PIN 18
#define CPIOT_MISO_PIN 19

File myFile;


void setup() {
  Serial.begin(115200);
  Serial.print("Initializing SD card...");
  SPIClass spi = SPIClass(VSPI);
  spi.begin(CPIOT_SCK_PIN /* SCK */, CPIOT_MISO_PIN /* MISO */, CPIOT_MOSI_PIN /* MOSI */, CPIOT_SS_PIN /* SS */);
  //  SD.begin(4 /* SS */, spi, 80000000);

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("/test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("/test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    Serial.println("read done");
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
}
