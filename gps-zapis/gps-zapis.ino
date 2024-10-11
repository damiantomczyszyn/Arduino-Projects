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
unsigned long startMilis = 0;


int buttonState = 0; 
String gpsDataText ="";

const int chipSelect = 10;

File file; 

SoftwareSerial Dta(4,3);
void setup() {
  startMilis = millis();
 
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
  unsigned long currentMillis = millis();
  
  if(raz){
    raz=false;

    file = SD.open("file.txt", FILE_WRITE);
    file.print("Start: ") ;   
    file.println(String(currentMillis));   
    file.flush();
    file.close();
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
      //Serial.write(gpsData);
      
      
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

    


    file = SD.open("file.txt", FILE_WRITE);
    file.println(); 
    file.print("Stop: ") ;   
    file.println(String(currentMillis)); 
    file.println(); 
    file.write((byte)'\n'); 


    file.flush();
    file.close();
    Serial.println("zapisane");
    delay(5000);//czekaj 30 minut


    file = SD.open("file.txt", FILE_WRITE);
    Serial.println("dzialam-dalej");
    file.print("dzialam-dalej: ") ;   
    file.println(String(millis())); 
    file.println(); 

    file.flush();
    file.close();
    
    

    
  }
}

