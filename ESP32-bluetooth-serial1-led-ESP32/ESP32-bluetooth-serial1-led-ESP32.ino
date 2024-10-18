#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
BluetoothSerial SerialBT;

#define LED_PIN 2 // Pin wbudowanej diody LED

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Wyłącz LED na początku
  delay(500);
  // Inicjalizacja Bluetooth
  SerialBT.begin("ESP32_A"); // Nazwa urządzenia
  delay(500);
  Serial.println("Bluetooth Device A is Ready to Pair");
    // Wyświetl adres MAC urządzenia
  const uint8_t* macAddr = esp_bt_dev_get_address();
  char macStr[18];
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
  Serial.print("Bluetooth MAC Address: ");
  Serial.println(macStr);
}


void loop() {
  // Odbieranie danych przez Bluetooth
  if (SerialBT.available()) {
    String command = SerialBT.readStringUntil('\n'); // Odczytaj komendę
    Serial.print("Odebrano przez Bluetooth: ");
    Serial.println(command);

    if (command == "ON") {
      digitalWrite(LED_PIN, HIGH); // Włącz diodę
      Serial.println("LED ON");
    } else if (command == "OFF") {
      digitalWrite(LED_PIN, LOW); // Wyłącz diodę
      Serial.println("LED OFF");
    } else {
      Serial.println("Odebrano wiadomość: " + command); // Wyświetl odebraną wiadomość
    }
  }

  // Przesyłanie danych z portu szeregowego do Bluetooth
  if (Serial.available()) {
    String text = Serial.readStringUntil('\n');
    SerialBT.println(text); // Wysyłanie tekstu do Bluetooth
  }
}
