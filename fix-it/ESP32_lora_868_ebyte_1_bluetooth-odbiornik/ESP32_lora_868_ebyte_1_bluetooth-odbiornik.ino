#define ENABLE_RSSI true

#include <HardwareSerial.h>
#include "LoRa_E220.h"
#include "BluetoothSerial.h"
#include "esp_bt_device.h"
#include "esp_bt_main.h"
#include "esp_gap_bt_api.h"

// Check if Bluetooth is available
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

// Check Serial Port Profile
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Port Profile for Bluetooth is not available or not enabled. It is only available for the ESP32 chip.
#endif


BluetoothSerial SerialBT;

// Definicja pinów dla ESP32
HardwareSerial LoRaSerial(2);
LoRa_E220 e220ttl(&LoRaSerial, 15, 2, 4);  // Inicjalizacja z odpowiednimi pinami

void setup() {
  Serial.begin(115200);  // Serial do debugowania
  String deviceName = "ESP32_BT";           // Nazwa urządzenia Bluetooth
  const char* devicePin = "1234";           // Hasło/pin do połączenia (max 4 cyfry)

  SerialBT.begin(deviceName);               // Ustawia nazwę Bluetooth
  esp_bt_gap_set_pin(ESP_BT_PIN_TYPE_FIXED, 4, (uint8_t*)devicePin);  // Ustawia PIN


  Serial.println("Bluetooth rozpoczął pracę. Połącz się z " + deviceName + " używając hasła " + devicePin);


  LoRaSerial.begin(9600, SERIAL_8N1, 16, 17);  // Serial dla LoRa
  e220ttl.begin();  // Inicjalizacja modułu LoRa

  // Ustawienie częstotliwości i aktywacja RSSI
  setFrequencyAndRSSI();

  Serial.println("Moduł LoRa - Gotowy do komunikacji na 868 MHz.");
}

void loop() {
  static bool isSender = true;

  if (isSender) {
    sendPacket();
  } else {
   // receivePacket();
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
       if (SerialBT.connected()) {
         SerialBT.println(rc.status.getResponseDescription());
         Serial.println(rc.data);
#ifdef ENABLE_RSSI
      SerialBT.print("RSSI: -"); 
      int rssi=rc.rssi;
      int wynik=255-rssi;
      SerialBT.println(wynik);  // Odczyt wartości RSSI
#endif
       }
      // Odczyt danych odebranej wiadomości
      Serial.println(rc.status.getResponseDescription());
      Serial.println(rc.data);
#ifdef ENABLE_RSSI
      int rssi=rc.rssi;
      int wynik=255-rssi;
      Serial.print("RSSI: -"); 
      Serial.println(wynik);  // Odczyt wartości RSSI
#endif
    }
  }
  
  // Odpowiedź na dane z Serial Monitor
  if (Serial.available()) {
    String input = Serial.readString();
    e220ttl.sendMessage(input);  // Wysłanie wiadomości wpisanej przez użytkownika
  }
}
