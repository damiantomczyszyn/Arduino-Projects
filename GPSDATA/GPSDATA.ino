#include <SoftwareSerial.h>
#include <SD.h> //Load SD library

int chipSelect = 8; //chip select pin for the MicroSD Card Adapter
File file; // file object that is used to read and write data

SoftwareSerial Dta(4,3);
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Dta.begin(9600);


  pinMode(chipSelect, OUTPUT); // chip select pin must be set to OUTPUT mode
  if (!SD.begin(chipSelect)) { // Initialize SD card
    Serial.println("Could not initialize SD card."); // if return value is false, something went wrong.
  }
  
  if (SD.exists("file.txt")) { // if "file.txt" exists, fill will be deleted
    Serial.println("File exists.");
    if (SD.remove("file.txt") == true) {
      Serial.println("Successfully removed file.");
    } else {
      Serial.println("Could not removed file.");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

 
  while(Dta.available()>0){
    byte gpsData=Dta.read();
    Serial.write(gpsData);


  }


}
