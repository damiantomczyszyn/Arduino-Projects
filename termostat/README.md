# Termostat

## Komponenty
* Arduino Uno
* DHT22
* Wyświetlacz LCD 16x2
* Przekaźnik
* Przyciski

## Połączenia

### LCD:
- RS (Pin 4) → Arduino Pin 2
- E (Pin 6) → Arduino Pin 3
- D4 (Pin 11) → Arduino Pin 4
- D5 (Pin 12) → Arduino Pin 5
- D6 (Pin 13) → Arduino Pin 6
- D7 (Pin 14) → Arduino Pin 7
- VSS, RW → GND (zasilanie)
- VDD → 5V (zasilanie)

### Czujnik DHT22:
- Pin 1 (VCC) → 5V
- Pin 2 (DATA) → Arduino Pin 8
- Pin 4 (GND) → GND

### Przyciski:
- Przycisk zwiększania temperatury → Arduino Pin 10
- Przycisk zmniejszania temperatury → Arduino Pin 11
- Drugi pin każdego przycisku połączony z GND

### Przekaźnik (sterujący urządzeniem grzewczym):
- Sterowanie (IN) → Arduino Pin 9
- VCC i GND → odpowiednio do 5V i GND
