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
unsigned long previousMillis = 0;
unsigned long interval = 60000;  // Co minutę (60,000 ms)

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
  }

  
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {    
    digitalWrite(ledgreenPin, HIGH);
    digitalWrite(ledredPin, LOW);

    if (file) {
       // Wywołanie flush() co kilka zapisów (np. co sekundę)
      if (currentMillis - previousMillis >= 1000) {
        file.flush();  // Zapisz bufor na kartę SD
        previousMillis = currentMillis;
      }
    

  // Zamykanie pliku co minutę i ponowne otwarcie
  if (currentMillis - previousMillis >= interval) {
      
        file.println("Auto-save at " + String(currentMillis));
        file.close();
    

    // Ponowne otwarcie pliku
      file = SD.open("file.txt", FILE_WRITE);
      if (!file) {
        Serial.println("Błąd otwarcia pliku.");
        //resetArduino()
        delay(10000000);        
      }
  }
    
    while (Dta.available() > 0) {

      byte gpsData = Dta.read();     
      file.write(gpsData);
      gpsDataText+=(char)gpsData;
      
      }
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


    file.println(); 
    file.print("Stop: ") ;   
    file.println(currentMillis); 
    file.println(); 
    //file.write((byte)'\n'); 
    // Zapis liczby jako ciągu znaków
    //file.write(String(currentMillis).c_str());
    //file.write((byte)'\n'); 


    file.flush();
    file.close();
    Serial.println("zapisane");
    Serial.println(currentMillis);
  
    delay(300000);//czekaj 5min
   while (!SD.begin(10)) { // sprawdz jak tam karta sd
     Serial.println("initialization failed! 2");
     delay(500);
    }
    if (!SD.exists("file.txt")) {
    Serial.println("restart file not exist");
    resetArduino();
    }
   Serial.println("initialization done! 2");



    file = SD.open("file.txt", FILE_WRITE);
    Serial.println("otworzylem-i-dzialam-dalej");
    file.print("dzialam-dalej: ") ;   
    file.println(String(millis())); 
    file.println(); 

  }
}

