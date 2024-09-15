#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Keypad.h>

#define CE_PIN 9
#define CSN_PIN 10

const byte numRows = 4; 
const byte numCols = 4; 

char keys[numRows][numCols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[numRows] = {6, 7, 8, A1};  // Zmiana pinu z 9 na A1 dla wiersza 4
byte colPins[numCols] = {3, 4, 5, A0};  // Piny dla kolumn

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, numRows, numCols);

RF24 radio(CE_PIN, CSN_PIN);

const byte address[6] = "00001"; // Adres dla komunikacji

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}
char znak [32] ="hello" ;

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.print("Wysłano: ");
    Serial.println(key);
    radio.write(&key, sizeof(key));
  }
  delay(2000);
  radio.write(&znak, sizeof(znak));
}
