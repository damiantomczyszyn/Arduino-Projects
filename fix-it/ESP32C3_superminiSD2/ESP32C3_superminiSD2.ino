#include <SPI.h>
#include <SD.h>

// Definiowanie pinów SPI dla ESP32 Supermini
#define SD_MISO 5   // GPIO5
#define SD_MOSI 6   // GPIO6
#define SD_SCK 4    // GPIO4
#define SD_CS 7     // GPIO7 (CS - Chip Select)

// Deklaracja obiektu pliku
File file;

void setup() {
  Serial.begin(115200);

  // Inicjalizacja karty SD
#ifdef REASSIGN_PINS
  SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);  // Użycie zdefiniowanych pinów
  if (!SD.begin(SD_CS)) {
#else
  if (!SD.begin()) {  // Użycie domyślnych pinów, jeśli REASSIGN_PINS nie jest zdefiniowane
#endif
    Serial.println("Błąd montowania karty SD");
    return;
  }
  

  // Otwieranie lub tworzenie pliku "znaki.txt"
  file = SD.open("/znaki.txt", FILE_APPEND);  // Dopisywanie do istniejącego pliku, jeśli plik nie istnieje, zostanie utworzony
  if (!file) {
    Serial.println("Błąd otwarcia pliku");
    return;
  }
  Serial.println("Karta SD zainicjowana pomyślnie.");
  // Generowanie losowych ciągów i zapis do pliku
  for (int i = 1; i <= 10; i++) {
    String prefix = "znaczki" + String(i);
    String randomString = generateRandomString(45);  // Generowanie ciągu o długości 20 znaków
    String line = prefix + randomString;
    
    // Zapis do pliku
    file.println(line);
    
    // Wyświetl w Serial Monitor
    Serial.println(line);
  }

  // Zakończenie zapisu i zamknięcie pliku
  file.close();
  Serial.println("Zakończono zapis do pliku.");
  delay(500);


}

void loop() {
  file = SD.open("/znaki.txt", FILE_APPEND);  // Dopisywanie do istniejącego pliku, jeśli plik nie istnieje, zostanie utworzony
  if (!file) 
  {
    Serial.println("Błąd otwarcia pliku");
    return;
  }

  String prefix = "znaczki";
  String randomString = generateRandomString(45);  // Generowanie ciągu o długości 20 znaków
  String line = prefix + randomString;
  file.println(line);
  file.println(String(millis()));
  Serial.println(line);
  file.close();
  delay(100);
}

// Funkcja generująca losowy ciąg o zadanej długości
String generateRandomString(int length) {
  String randomString = "";
  const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

  for (int i = 0; i < length; i++) {
    int index = random(0, sizeof(characters) - 1);
    randomString += characters[index];
  }

  return randomString;
}
