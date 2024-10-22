#include <Keypad.h>
#include <esp_now.h>
#include <WiFi.h>

// Definicja wymiarów matrycy keypad
const byte ROWS = 4; 
const byte COLS = 4; 

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

// Struktura danych do wysłania
typedef struct struct_message {
    char button;  // Wciśnięty przycisk
    bool pressed; // Czy przycisk jest wciśnięty
} struct_message;

// Adres MAC odbiorcy
//uint8_t receiverAddress[] = {0xb0, 0xa7, 0x32, 0x14, 0x4b, 0x1c};//spalonyESP
uint8_t receiverAddress[] = {0xd0, 0xef, 0x76, 0x56, 0xee, 0xe4};//nowy 38pinowy
// Struktura wiadomości
struct_message myData;

// Funkcja wywoływana przy sukcesie wysłania danych
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print("\nLast Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Zmienna do przechowywania stanu przycisku
bool currentKeyPressed = false; // Czy klawisz jest aktualnie wciśnięty

void setup() {
    Serial.begin(115200);
    delay(1000);  // Daj czas na otwarcie portu szeregowego

    // Inicjalizacja ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Dodanie odbiorcy
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, receiverAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;
    
    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    char key = keypad.getKey();

    if (key) {
        // Jeśli klawisz został wciśnięty
        if (!currentKeyPressed) {
            myData.button = key;
            myData.pressed = true; // Klawisz wciśnięty
            esp_now_send(receiverAddress, (uint8_t *)&myData, sizeof(myData));
            Serial.print("Wciśnięty klawisz: ");
            Serial.println(key);
            currentKeyPressed = true; // Ustaw stan na wciśnięty
        }
    } else {
        // Jeśli klawisz został puszczony
        if (currentKeyPressed) {
            myData.pressed = false; // Klawisz puszczony
            esp_now_send(receiverAddress, (uint8_t *)&myData, sizeof(myData));
            Serial.print("Klawisz puszczony: ");
            Serial.println(myData.button); // Wypisz puszczony klawisz
            currentKeyPressed = false; // Ustaw stan na puszczony
        }
    }

    delay(100);  // Krótkie opóźnienie dla stabilności
}