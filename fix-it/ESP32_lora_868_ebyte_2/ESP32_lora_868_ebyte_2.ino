#include <HardwareSerial.h>



HardwareSerial LoRaSerial(2);  // Użycie Serial2 dla LoRa (TX na GPIO17, RX na GPIO16)
#define M0_PIN 2
#define M1_PIN 4
#define AUX_PIN 15



void configureFrequency() {
  Serial.println("Konfiguracja częstotliwości na 868 MHz...");
  
  LoRaSerial.write(0xC1);  // Adresowanie zapisu rejestrów
  LoRaSerial.write(0x00);  // Adres wysokiego bajtu częstotliwości
  LoRaSerial.write(0x34);  // Ustawienie częstotliwości na 868 MHz (bajty do potwierdzenia w dokumentacji)
  
  delay(100);  // Oczekiwanie na zapis konfiguracji
  Serial.println("Częstotliwość ustawiona na 868 MHz.");
}

void setup() {
  Serial.begin(115200);
  LoRaSerial.begin(9600, SERIAL_8N1, 16, 17);  // Inicjalizacja portu szeregowego dla LoRa
  configureFrequency();  // Wywołanie funkcji konfiguracji częstotliwości
  
  pinMode(M0_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(AUX_PIN, INPUT);

  // Ustawienie trybu Normal Mode (M0 = LOW, M1 = LOW)
  digitalWrite(M0_PIN, LOW);
  digitalWrite(M1_PIN, LOW);

  Serial.println("Moduł LoRa - test komunikacji na zmianę");
}

void loop() {
  static bool isSender = true;  // Flaga, czy moduł wysyła, czy odbiera
  
  if (isSender) {
    sendPacket();
  } else {
    receivePacket();
  }

  isSender = !isSender;  // Zmiana roli
  delay(2000);  // Czas oczekiwania na zmianę trybu
}

void sendPacket() {
  Serial.println("Wysyłanie wiadomości...");
  LoRaSerial.print("Hello from ESP32");
  delay(50);  // Czas na wysłanie wiadomości
}

void receivePacket() {
  Serial.println("Oczekiwanie na wiadomość...");
  while (LoRaSerial.available()) {
    String received = LoRaSerial.readString();
    Serial.print("Odebrano: ");
    Serial.println(received);
    
    int rssi = getRSSI();  // Uzyskanie wartości RSSI
    Serial.print("RSSI: ");
    Serial.println(rssi);
  }
}

int getRSSI() {
  // Uzyskanie RSSI przez AUX (wymaga dodatkowej konfiguracji modułu)
  if (digitalRead(AUX_PIN) == LOW) {
    // Przykładowa wartość dla RSSI (można dostosować do rzeczywistej metody odczytu)
    return random(-120, -40);  // Symulowana wartość RSSI
  }
  return -1;  // Jeśli brak sygnału
}
