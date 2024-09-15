# Odczyt danych z czujnika GPS

## Komponenty:
* Arduino Uno
* NEO-M8N

## Połączenia

### Moduł GPS (SoftwareSerial):
- **RX (odbiór danych)** → Arduino Pin 4
- **TX (transmisja danych)** → Arduino Pin 3
- **Zasilanie modułu GPS**:
  - VCC → 5V
  - GND → GND

### Adapter karty MicroSD:
- **CS (chip select)** → Arduino Pin 8
- **MOSI** → Arduino Pin 11
- **MISO** → Arduino Pin 12
- **SCK** → Arduino Pin 13
- **VCC** → 5V
- **GND** → GND

