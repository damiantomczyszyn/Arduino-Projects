#include <esp_now.h>
#include <WiFi.h>

#define LEWY_SILNIK 22
#define PRAWY_SILNIK 23

#define LEWY_SILNIK_KIERUNEK 18
#define PRAWY_SILNIK_KIERUNEK 19
#define SILNIK_KOSZACY 21

int lewySilnikSpeed = 0;
int prawySilnikSpeed = 0;
int kierunekLewySilnik = 0;
int kierunekPrawySilnik = 0;
int silnikKoszacy=1;

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


        if(incomingData.button=='1')
        {
          Serial.print("Wciśnięty klawisz: jeden");
          if(lewySilnikSpeed+11 < 255)
          lewySilnikSpeed +=10;
        }


        if(incomingData.button=='A')
        {
          Serial.print("Wciśnięty klawisz: A");
          if(prawySilnikSpeed+11 < 255)
          prawySilnikSpeed +=10;
        }

        if(incomingData.button=='*')
        {
          Serial.print("Wciśnięty klawisz: *");
          if(lewySilnikSpeed-11 > 0)
          lewySilnikSpeed -=10;
        }

                if(incomingData.button=='3')
        {
          Serial.print("Wciśnięty klawisz: trzy");
          
          lewySilnikSpeed =0;
          prawySilnikSpeed =0;
        }


        if(incomingData.button=='D')
        {
          Serial.print("Wciśnięty klawisz: D");
          if(prawySilnikSpeed-11 >0)
          prawySilnikSpeed -=10;
        }


        if(incomingData.button=='5')
        {
          Serial.print("Wciśnięty klawisz: piec");
          prawySilnikSpeed = 80;
          lewySilnikSpeed = 80;

          kierunekLewySilnik=1;
          kierunekPrawySilnik=0;
        }

        if(incomingData.button=='7')
        {
          Serial.print("Wciśnięty klawisz: siedem");
          prawySilnikSpeed = 80;
          lewySilnikSpeed = 0;
          kierunekLewySilnik=1;
          kierunekPrawySilnik=0;
        }
        if(incomingData.button=='9')
        {
          Serial.print("Wciśnięty klawisz: dziewiec");
          prawySilnikSpeed =0;
          lewySilnikSpeed = 80;
          kierunekLewySilnik=1;
          kierunekPrawySilnik=0;
        }
        if(incomingData.button=='0')
        {
          Serial.print("Wciśnięty klawisz: zero");
          prawySilnikSpeed = 80;
          lewySilnikSpeed = 80;

          kierunekLewySilnik=0;
          kierunekPrawySilnik=1;
        }

        if(incomingData.button=='8')
        {
          Serial.print("Wciśnięty klawisz: osiem");
          if(silnikKoszacy==1)
          {
            silnikKoszacy=0;
          }
          else{
            silnikKoszacy=1;
          }

        }




        previousState = true; // Ustaw stan na wciśnięty
        analogWrite(PRAWY_SILNIK, prawySilnikSpeed);
        analogWrite(LEWY_SILNIK, lewySilnikSpeed);

        digitalWrite(PRAWY_SILNIK_KIERUNEK, kierunekPrawySilnik);
        digitalWrite(LEWY_SILNIK_KIERUNEK, kierunekLewySilnik); 

        digitalWrite(SILNIK_KOSZACY, silnikKoszacy); 

    } 
    else if (previousState) {
        Serial.print("Klawisz puszczony: ");
        Serial.println(incomingData.button);
        previousState = false; // Ustaw stan na puszczony
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LEWY_SILNIK, OUTPUT);
    pinMode(PRAWY_SILNIK, OUTPUT);
    pinMode(SILNIK_KOSZACY, OUTPUT);
    pinMode(PRAWY_SILNIK_KIERUNEK, OUTPUT);
    pinMode(LEWY_SILNIK_KIERUNEK, OUTPUT);
    digitalWrite(SILNIK_KOSZACY,silnikKoszacy);
    

    delay(1000);  // Daj czas na otwarcie portu szeregowego
    Serial.println("Start");

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
    
}
