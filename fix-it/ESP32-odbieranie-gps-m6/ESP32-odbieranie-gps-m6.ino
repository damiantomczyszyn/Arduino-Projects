#include <EEPROM.h>
#include <SPI.h>
#include "SD.h"
#include "FS.h"
#include "TinyGPS++.h"

#define DEBUG true

#define RXD2 16
#define TXD2 17

const int CS = 5;
int log_counter = 0;
int nfiles = 0;
String gnss_dir = "GNSS_LOGS";
String log_buffer = "";

TinyGPSPlus gps;

void Serial_Print(String msg) {
#if DEBUG
  Serial.print(msg);
#endif
}

void setup() {
#if DEBUG
  Serial.begin(115200);
#endif
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  EEPROM.begin(64);
  Serial_Print("\n\r*************** GPS_ON ***************\n\r");
  SD_INIT();
  listDir(SD, "/", 0);
  createDir(SD, "/" + gnss_dir);
  listDir(SD, "/" + gnss_dir, 0);
  Serial_Print("\n\r\n\r[SETUP COMPLETE]\n\r\n\r");
}

/**********************************************************************
   SDCard Functions
 **********************************************************************/

void SD_INIT() {
  Serial_Print("\n\rInitializing SD Card...\n\r");
  if (!SD.begin(CS)) {
    Serial_Print("Initialization Failed!\n\r");
    delay(1000);
    return;
  }
  Serial_Print("Initialization Success!\n\r");
  Serial_Print("-------SD Card Info-------\n\r");
  Serial_Print("SD Card Type:\t");
  uint8_t cardType = SD.cardType();
  uint64_t bytes = SD.totalBytes();
  uint64_t used_bytes = SD.usedBytes();
  if (cardType == CARD_MMC) Serial_Print("MMC\n\r");
  else if (cardType == CARD_SD) Serial_Print("SDSC\n\r");
  else if (cardType == CARD_SDHC) Serial_Print("SDHC\n\r");
  else if (cardType == CARD_NONE) Serial_Print("No SD Card Attached\n\r");
  else Serial_Print("UNKNOWN\n\r");

  Serial_Print("Volume(MB):\t" + String((float)bytes / (1000 * 1000)) + "\n\r");
  Serial_Print("Volume(GB):\t" + String((float)bytes / (1000 * 1000 * 1000)) + "\n\r");
  Serial_Print("Used(MB):\t" + String((float)used_bytes / (1000 * 1000)) + "\n\r");
  Serial_Print("Used(GB):\t" + String((float)used_bytes / (1000 * 1000 * 1000)) + "\n\r");
  Serial_Print("--------------------------\n\r");
}

String listDir(fs::FS &fs, String dirname, uint8_t levels) {
  String listing = "";
  int count = 0;
  Serial_Print("Listing directory: " + dirname + "\n\r");
  File root = fs.open(dirname);
  if (!root || !root.isDirectory()) {
    Serial_Print("Failed to open directory\n\r");
    return "-1,";
  }
  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial_Print("  DIR : " + String(file.name()) + "\n\r");
      if (levels) listDir(fs, file.name(), levels - 1);
    } else {
      count += 1;
      Serial_Print("  FILE: " + String(file.name()) + "  SIZE: " + String(file.size()) + "\n\r");
      listing = listing + "," + String(file.name()) + "," + String(file.size());
    }
    file = root.openNextFile();
  }
  nfiles = count;
  return String(count) + listing;
}

void createDir(fs::FS &fs, String path) {
  if (SD.exists(path)) {
    Serial_Print("Dir " + path + " Exists...\n\r");
    return;
  }
  Serial_Print("Creating Dir: " + path + "\n\r");
  if (fs.mkdir(path)) Serial_Print("Dir created\n\r");
  else Serial_Print("mkdir failed\n\r");
}

void appendFile(fs::FS &fs, String path, String message) {
  File file = fs.open(path, FILE_APPEND);
  if (!file) return;
  file.print(message);
  file.close();
}

/**********************************************************************
   Loop Function
 **********************************************************************/

void loop() {
  while (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
      if (gps.location.isUpdated()) {
        String log = String(gps.location.lat(), 6) + "," +
                     String(gps.location.lng(), 6) + "," +
                     String(gps.altitude.meters(), 2) + "," +
                     String(gps.speed.kmph(), 2) + "\n";

        Serial_Print("Logging: " + log);
        appendFile(SD, "/" + gnss_dir + "/GPS_LOG.log", log);
      }
    }
  }
}
