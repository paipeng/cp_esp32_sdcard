
#include "public.h"
#include <SPI.h>
#include <SD.h>


File myFile;


void setup(){
  Serial.begin(115200);
  Serial.print("Initializing SD card...");
  SPIClass spi = SPIClass(VSPI);
  spi.begin(18 /* SCK */, 19 /* MISO */, 23 /* MOSI */, 4 /* SS */);
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
  
void loop(){
  
}
