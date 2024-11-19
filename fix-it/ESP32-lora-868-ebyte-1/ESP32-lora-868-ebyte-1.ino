#define ENABLE_RSSI true

#include <HardwareSerial.h>
#include "LoRa_E220.h"

// Definicja pinów dla ESP32
HardwareSerial LoRaSerial(2);
LoRa_E220 e220ttl(&LoRaSerial, 15, 2, 4);  // Inicjalizacja z odpowiednimi pinami

void setup() {
  Serial.begin(115200);  // Serial do debugowania
  LoRaSerial.begin(9600, SERIAL_8N1, 16, 17);  // Serial dla LoRa
  e220ttl.begin();  // Inicjalizacja modułu LoRa

  // Ustawienie częstotliwości i aktywacja RSSI
  setFrequencyAndRSSI();

  Serial.println("Moduł LoRa - Gotowy do komunikacji na 868 MHz.");
}

void loop() {
  static bool isSender = true;

  if (isSender) {
   // sendPacket();
  } else {
    receivePacket();
  }

  isSender = !isSender;  // Zmiana roli
  //delay(2000);  // Czas oczekiwania między wysyłaniem a odbiorem
}

void setFrequencyAndRSSI() {
  Serial.println("Ustawianie częstotliwości na 868 MHz i aktywacja RSSI...");
  
  // Uzyskanie konfiguracji
  ResponseStructContainer configurationResponse = e220ttl.getConfiguration();
  if (configurationResponse.status.code == 1) {  // Sprawdzenie statusu
    Configuration configuration = *(Configuration*)configurationResponse.data;  // Odczytanie danych konfiguracji
    configuration.CHAN = 36;  // Ustaw kanał dla 868 MHz
    configuration.TRANSMISSION_MODE.enableRSSI = RSSI_ENABLED;  // Włączenie RSSI

    e220ttl.setConfiguration(configuration);  // Zastosowanie konfiguracji
    Serial.println("Częstotliwość i RSSI ustawione.");
  } else {
    Serial.println("Błąd przy konfiguracji modułu.");
  }
}

void sendPacket() {
  String message = "Hello from ESP32";  // Wiadomość do wysłania
  ResponseStatus rs = e220ttl.sendMessage(message);  // Wysyłanie wiadomości
  Serial.println("Wysyłanie wiadomości...");
  Serial.println(rs.getResponseDescription());
}

void receivePacket() {
  if (e220ttl.available() > 1) {
    ResponseContainer rc;
#ifdef ENABLE_RSSI
    rc = e220ttl.receiveMessageRSSI();  // Odbieranie wiadomości z RSSI
#else
    rc = e220ttl.receiveMessage();  // Odbieranie wiadomości bez RSSI
#endif

    // Sprawdzenie statusu odbioru
    if (rc.status.code != 1) {
      Serial.println(rc.status.getResponseDescription());
    } else {
      // Odczyt danych odebranej wiadomości
      Serial.println(rc.status.getResponseDescription());
      Serial.println(rc.data);
#ifdef ENABLE_RSSI
      Serial.print("RSSI: "); 
      Serial.println(rc.rssi, DEC);  // Odczyt wartości RSSI
#endif
    }
  }
  
  // Odpowiedź na dane z Serial Monitor
  if (Serial.available()) {
    String input = Serial.readString();
    e220ttl.sendMessage(input);  // Wysłanie wiadomości wpisanej przez użytkownika
  }
}
