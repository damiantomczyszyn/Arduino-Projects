#define ENABLE_RSSI true

#include "Arduino.h"
#include "LoRa_E220.h"

// Definicja pinów dla ESP32
HardwareSerial LoRaSerial(2);  // Użycie Serial2 dla LoRa (TX na GPIO17, RX na GPIO16)
LoRa_E220 e220ttl(&LoRaSerial, 15, 2, 4);  // Inicjalizacja z odpowiednimi pinami (RX, TX, AUX, M0, M1)

void setup() {
  Serial.begin(115200);  // Serial do debugowania
  LoRaSerial.begin(9600, SERIAL_8N1, 16, 17);  // Serial dla LoRa

  if (!e220ttl.begin()) {
      Serial.println("Błąd inicjalizacji E220");
  } else {
      Serial.println("Inicjalizacja E220 udana");
  }
  
  Serial.println("Odbiornik gotowy. Czekam na wiadomość...");
}


void loop() {
  // Sprawdzenie, czy są dostępne dane
  if (e220ttl.available() > 1) {
    // Odbieranie wiadomości
#ifdef ENABLE_RSSI
    ResponseContainer rc = e220ttl.receiveMessageRSSI();
#else
    ResponseContainer rc = e220ttl.receiveMessage();
#endif

    // Sprawdzenie statusu
    if (rc.status.code != 1) {
      Serial.println(rc.status.getResponseDescription());
    } else {
      // Wyświetlenie odebranej wiadomości
      Serial.print("Odebrano: ");
      Serial.println(rc.data);
#ifdef ENABLE_RSSI
	ResponseContainer rc = e220ttl.receiveMessageRSSI();
	Serial.print("Raw Response: ");
	Serial.println(rc.status.code);  // Sprawdzenie kodu statusu
	Serial.println(rc.data);  // Wypisanie danych
	if (rc.status.code != 1) {
		Serial.println(rc.status.getResponseDescription());
	} else {
		Serial.print("RSSI: ");
		Serial.println(rc.rssi, DEC);  // Powinno być w zakresie -120 do 0
	}
#endif

    }
  }
}
