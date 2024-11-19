#define ENABLE_RSSI true

#include "Arduino.h"
#include "LoRa_E220.h"

// Definicja pinów dla ESP32
HardwareSerial LoRaSerial(2);  // Serial2 dla LoRa (TX na GPIO17, RX na GPIO16)
LoRa_E220 e220ttl(&LoRaSerial, 15, 2, 4);  // Inicjalizacja z odpowiednimi pinami (RX, TX, AUX, M0, M1)

void setup() {
  Serial.begin(115200);  // Serial do debugowania
  LoRaSerial.begin(9600, SERIAL_8N1, 16, 17);  // Serial dla LoRa

  // Rozpocznij komunikację z modułem
  if (e220ttl.begin()) {
    Serial.println("Nadajnik gotowy do wysyłania wiadomości.");
  } else {
    Serial.println("Błąd inicjalizacji modułu E220.");
  }
}

void loop() {
  // Wiadomość do wysłania
  String message = "Hello from ESP32";

  // Wysyłanie wiadomości
  ResponseStatus rs = e220ttl.sendMessage(message);

  // Sprawdzenie statusu wysyłania
  if (rs.code == 1) {
    Serial.println("Wiadomość wysłana pomyślnie.");
  } else {
    Serial.print("Błąd wysyłania wiadomości: ");
    Serial.println(rs.getResponseDescription());
  }

  // Odczekanie 2 sekundy przed wysłaniem kolejnej wiadomości
  delay(2000);
}
