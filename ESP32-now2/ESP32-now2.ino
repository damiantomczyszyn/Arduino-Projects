#include <esp_now.h>
#include <WiFi.h>

// Struktura danych odbieranych
typedef struct struct_message {
    char button;  // Odbierany wciśnięty przycisk
    bool pressed; // Czy przycisk jest wciśnięty
} struct_message;

// Zmienna do przechowywania odebranych danych
struct_message incomingData;
bool previousState = false;  // Zmienna do przechowywania poprzedniego stanu przycisku

// Funkcja wywoływana po odebraniu danych
void OnDataRecv(const esp_now_recv_info* sender, const uint8_t* incomingDataPtr, int len) {
    memcpy(&incomingData, incomingDataPtr, sizeof(incomingData)); // Skopiuj dane do incomingData

    // Sprawdzenie stanu wciśnięcia przycisku
    if (incomingData.pressed) {
        Serial.print("Wciśnięty klawisz: ");
        Serial.println(incomingData.button);
        previousState = true; // Ustaw stan na wciśnięty
    } else if (previousState) {
        Serial.print("Klawisz puszczony: ");
        Serial.println(incomingData.button);
        previousState = false; // Ustaw stan na puszczony
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);  // Daj czas na otwarcie portu szeregowego

    // Inicjalizacja ESP-NOW
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Rejestrowanie funkcji odbierającej dane
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    // Pętla bezczynności
}
