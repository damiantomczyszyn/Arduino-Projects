#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <avr/wdt.h>

void resetArduino() {
  wdt_enable(WDTO_15MS); 
  while (1) {} 
}

const int buttonPin = 2;  // numer pinu przycisku
const int ledgreenPin = 6;    // numer pinu zielonej diody LED
const int ledredPin = 7;    // numer pinu czerwonej diody LED
unsigned long startMillis = 0;
unsigned long previousMillis = 0;
unsigned long interval = 60000;  // Co minutę (60,000 ms)

int buttonState = 0; 
String gpsDataText = "";
String buffer = "";  // Bufor do zapisywania danych przed ich zapisaniem na SD

const int chipSelect = 10;
File file; 

SoftwareSerial Dta(4, 3);  // Ustawienia SoftwareSerial

void setup() {
  startMillis = millis();
  
  Serial.begin(9600);
  Dta.begin(9600);

  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  if (SD.exists("file.txt")) {
    Serial.println("File exists.");
    if (SD.remove("file.txt")) {
      Serial.println("Successfully removed file.");
    } else {
      Serial.println("Could not remove file.");
    }
  }

  pinMode(ledgreenPin, OUTPUT);
  pinMode(ledredPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

bool raz = true;

void loop() {
  unsigned long currentMillis = millis();

  if (raz) {
    raz = false;
    file = SD.open("file.txt", FILE_WRITE);
    file.print("Start: ");
    file.println(String(currentMillis));
    file.close();
  }

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {    
    digitalWrite(ledgreenPin, HIGH);
    digitalWrite(ledredPin, LOW);

    while (Dta.available() > 0) {
      byte gpsData = Dta.read();
      buffer += (char)gpsData;  // Zapisujemy dane do bufora
    }

    buffer.trim();
    if (buffer.length() > 0) {
      Serial.println(buffer);  // Wyświetla zebrane dane GPS w postaci tekstu
    }

    // Co minutę zapisujemy bufor na kartę SD
    if (currentMillis - previousMillis >= interval) {
      file = SD.open("file.txt", FILE_WRITE);
      if (file) {
        file.println("Auto-save at " + String(currentMillis));
        file.print(buffer);  // Zapisz bufor na kartę SD
        file.flush();  // Zapisz dane na kartę
        file.close();
        buffer = "";  // Wyczyść bufor po zapisie
        previousMillis = currentMillis;
      } else {
        Serial.println("Błąd otwarcia pliku.");
        resetArduino();
      }
    }

  } else {
    Serial.println("low");
    digitalWrite(ledgreenPin, LOW);
    digitalWrite(ledredPin, HIGH);

    // Zamykamy i zapisujemy plik przy wyłączonym przycisku
    file = SD.open("file.txt", FILE_WRITE);
    if (file) {
      file.println();
      file.print("Stop: ");
      file.println(currentMillis);
      file.close();
    }
    delay(300000);  // Czekaj 5 minut

    // Sprawdź status karty SD
    while (!SD.begin(chipSelect)) {
      Serial.println("initialization failed! 2");
      delay(500);
    }
    if (!SD.exists("file.txt")) {
      Serial.println("restart file not exist");
      resetArduino();
    }
    Serial.println("initialization done! 2");

    file = SD.open("file.txt", FILE_WRITE);
    file.print("dzialam-dalej: ");
    file.println(String(millis()));
    file.println();
    file.close();
  }
}
