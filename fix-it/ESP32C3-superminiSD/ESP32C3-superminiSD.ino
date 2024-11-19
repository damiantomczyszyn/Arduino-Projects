

#include "FS.h"
#include "SD.h"
#include "SPI.h"



void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

#ifdef REASSIGN_PINS
  SPI.begin(sck, miso, mosi, cs);
  if (!SD.begin(cs)) {
#else
  if (!SD.begin()) {
#endif
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);



  File root = fs.open(dirname)

 if (!SD.begin(cs)) {
    Serial.println("Błąd inicjalizacji karty SD");
    return;
  }
  Serial.println("Karta SD zainicjowana pomyślnie.");

  // Otwieranie lub tworzenie pliku "znaki.txt"
  file = SD.open("/znaki.txt", FILE_APPEND);
  if (!file) {
    Serial.println("Błąd otwarcia pliku");
    return;
  }



 for (int i = 1; i <= 10; i++) {
    String prefix = "znaczki" + String(i);
    String randomString = generateRandomString(20);
    String line = prefix + randomString;
    
    // Zapis do pliku
    file.println(line);
    
    // Wyświetl w Serial Monitor
    Serial.println(line);
  }

  // Zakończenie zapisu i zamknięcie pliku
  file.close();
  Serial.println("Zakończono zapis do pliku.");
}
}

void loop() {


}



String generateRandomString(int length) {
  String randomString = "";
  const char characters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

  for (int i = 0; i < length; i++) {
    int index = random(0, sizeof(characters) - 1);
    randomString += characters[index];
  }

  return randomString;
}
