#include <Keypad.h>

// Definicja wymiarów matrycy keypad
const byte ROWS = 4; // cztery wiersze
const byte COLS = 4; // cztery kolumny

// Definicja przycisków
char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

// Podłączenie pinów do ESP32
byte rowPins[ROWS] = {23, 22, 21, 19}; // Piny do wierszy
byte colPins[COLS] = {18, 5, 12, 13};  // Piny do kolumn

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
    // Inicjalizacja portu szeregowego
    Serial.begin(115200);
    delay(1000);  // Daj czas na otwarcie portu szeregowego
}

void loop() {
    char key = keypad.getKey(); // Odczytaj wciśnięty przycisk
    
    if (key) { // Jeśli przycisk został wciśnięty
        Serial.print("Wciśnięty klawisz: ");
        Serial.println(key);
    }
}
