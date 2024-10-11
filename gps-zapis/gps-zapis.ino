#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <avr/wdt.h>

void resetArduino() {
  wdt_enable(WDTO_15MS); 
  while (1) {} 
}


const int buttonPin = 2;  // the number of the pushbutton pin
const int ledgreenPin = 6;    // the number of the LED pin
const int ledredPin = 7;    // the number of the LED pin


int buttonState = 0; 
String gpsDataText ="";

const int chipSelect = 10;

File file; 

SoftwareSerial Dta(4,3);
void setup() {
 
Serial.begin(9600);
Dta.begin(9600);


Serial.print("Initializing SD card...");

  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");



  if (SD.exists("file.txt")) { // if "file.txt" exists, fill will be deleted
    Serial.println("File exists.");
    if (SD.remove("file.txt") == true) {
      Serial.println("Successfully removed file.");
    } else {
      Serial.println("Could not removed file.");

      while ( (SD.exists("file.txt")) )
      {
        Serial.println("File exists.");
    if (SD.remove("file.txt") == true) {
      Serial.println("Successfully removed file.");
    } else {
      Serial.println("Could not removed file.");
      }
    }
    }
  }
  

    pinMode(ledgreenPin, OUTPUT);
    pinMode(ledredPin, OUTPUT);
  
  pinMode(buttonPin, INPUT);

}
bool raz = true;
void loop() {

  if(raz){
    delay(500);
    //file = SD.open("file.txt", FILE_WRITE);
    delay(500);
    raz=false;
  }
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    
    digitalWrite(ledgreenPin, HIGH);
    digitalWrite(ledredPin, LOW);

   file = SD.open("file.txt", FILE_WRITE);
  
  if (file) {
    

    
    while (Dta.available() > 0) {
      byte gpsData = Dta.read();
      Serial.write(gpsData);
      
      
      file.write(gpsData);
      gpsDataText+=(char)gpsData;
      
      }
      file.close();
      gpsDataText.trim();
  if (gpsDataText.length() > 0) {  // trim() usuwa białe znaki (spacje, nowe linie)
    Serial.println(gpsDataText);  // Wyświetla zebrane dane GPS w postaci tekstu
  }
      gpsDataText="";
    }
   else {
    Serial.println("Could not open file (writing).");
    resetArduino();
        }
  }
  else 
  {
    Serial.println("low");
    digitalWrite(ledgreenPin, LOW);   
    digitalWrite(ledredPin, HIGH);
    delay(1000*60*10);//czekaj 10 minut
    
    

    
  }
}

