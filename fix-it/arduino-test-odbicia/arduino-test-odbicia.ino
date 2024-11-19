int czujnikPin1 = A0;  // Pierwszy pin sygnałowy podłączony do pinu analogowego A0
int czujnikPin2 = A1;  // Drugi pin sygnałowy podłączony do pinu analogowego A1
int ledPin = LED_BUILTIN;  // Wbudowany LED (pin 13 na większości modeli Arduino)
bool ledStan = LOW;  // Zmienna do śledzenia stanu LED-a

void setup() {
  pinMode(ledPin, OUTPUT);      // Ustawienie pinu LED jako wyjście
  Serial.begin(9600);           // Uruchomienie komunikacji szeregowej
}

void loop() {
  int wartoscCzujnik1 = analogRead(czujnikPin1);  // Odczyt analogowy pinu 1
  int wartoscCzujnik2 = analogRead(czujnikPin2);  // Odczyt analogowy pinu 2
  
  // Obliczamy różnicę między odczytami obu czujników
  int roznica = abs(wartoscCzujnik1 - wartoscCzujnik2);
  
 // Serial.print("Czujnik 1 (A0): ");
  Serial.print(wartoscCzujnik1);  // Wartość od 0 do 1023 (analogowy odczyt)

  Serial.print("\t");  
  
 // Serial.print("Czujnik 2 (A1): ");
  Serial.print(wartoscCzujnik2);  // Wartość od 0 do 1023 (analogowy odczyt)
  Serial.print("\t");  

 // Serial.print("Różnica między czujnikami: ");
  Serial.println(roznica);

  // Zmiana stanu wbudowanego LED-a co iterację pętli
  if (ledStan == LOW) {
    ledStan = HIGH;  // Zmień stan na HIGH
  } else {
    ledStan = LOW;   // Zmień stan na LOW
  }
  digitalWrite(ledPin, ledStan);  // Ustawienie stanu LED-a
  
  delay(100);  // Opóźnienie dla stabilności odczytu
}
