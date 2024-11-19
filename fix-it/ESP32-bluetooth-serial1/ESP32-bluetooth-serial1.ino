#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);  // Monitor szeregowy
  SerialBT.begin("ESP32_Device"); // Nazwa Bluetooth
  Serial.println("Używam wbudowanego Bluetooth ESP32");
}

void loop() {
  if (SerialBT.available()) {
    Serial.write(SerialBT.read()); // Odbieranie danych przez Bluetooth
  }

  if (Serial.available()) {
    SerialBT.write(Serial.read());  // Wysyłanie danych przez Bluetooth
  }
}
