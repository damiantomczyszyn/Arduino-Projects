# Odczyt danych z czujnika BME i udostępnienie ich na webserwerze

## Komponenty:
* ESP32
* BME280

## Połączenia

### Moduł BME280 (I2C):
- **VIN** → 3.3V lub 5V (zależnie od wersji modułu)
- **GND** → GND
- **SCL** → Arduino Pin A5 (ESP32 Pin 22)
- **SDA** → Arduino Pin A4 (ESP32 Pin 21)
- Opcjonalnie, jeśli moduł BME280 używa interfejsu SPI:
  - **SCK** → Arduino Pin 14
  - **MISO** → Arduino Pin 12
  - **MOSI** → Arduino Pin 13
  - **CS** → Arduino Pin 15

### Czujnik DHT22:
- **VCC** → 3.3V
- **GND** → GND
- **DATA** → Arduino Pin 2

### Moduł WiFi (ESP32):
- **VIN** → 5V (jeśli używasz ESP32)
- **GND** → GND
- **GPIO 22** → SCL (do BME280)
- **GPIO 21** → SDA (do BME280)

### Czujnik poziomu wody:
- **OUT** → Arduino Pin A0
- **VCC** → 5V
- **GND** → GND

