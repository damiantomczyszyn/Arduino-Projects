# Zapis z gps na kartę SD

## Komponenty:
* Arduino Uno
* NEO-M8N
* Przycisk
  
## Połączenia

### LED:
- Zielona dioda (ledgreenPin) → Arduino Pin 6
- Czerwona dioda (ledredPin) → Arduino Pin 7
- Drugi pin każdej diody → GND

### Przycisk:
- Jeden pin przycisku → Arduino Pin 2
- Drugi pin przycisku → GND

### Moduł GPS (SoftwareSerial):
- RX (odbiór danych) → Arduino Pin 4
- TX (transmisja danych) → Arduino Pin 3
- Zasilanie modułu GPS:
  - VCC → 5V
  - GND → GND

### Karta SD:
- CS (chip select) → Arduino Pin 10
- MOSI → Arduino Pin 11
- MISO → Arduino Pin 12
- SCK → Arduino Pin 13
- VCC → 5V
- GND → GND
