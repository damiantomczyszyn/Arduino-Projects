#include <LiquidCrystal.h> 
#include "DHT.h" //by Adafruit 1.4.6

#define DHT11_PIN 8
#define DHTTYPE DHT22
#define WLACZNIKPODGRZEWANIA 9
#define stanOFF 1
#define stanON 0
DHT dht(DHT11_PIN, DHTTYPE);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
float ustawionaTemperatura = 50.0;
int buttonPinTempUp = 10;
int buttonPinTempDown = 11;

void pinInit()
{
  pinMode(WLACZNIKPODGRZEWANIA, OUTPUT);
  pinMode(buttonPinTempUp, INPUT_PULLUP);
  pinMode(buttonPinTempDown, INPUT_PULLUP);
}

void dhtInit()
{
  dht.begin();
} 

void lcdInit()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  //lcd.print("Pierwsza linia"); 
}

float getHumidity()
{
  Serial.print(" %, Hum: ");
  Serial.println(dht.readHumidity());
  return dht.readHumidity();
}

float getTemperature()
{
  Serial.print(" %, Temp: ");
  Serial.println(dht.readTemperature());
  return dht.readTemperature();
}

bool czyWlaczacPodgrzewanie()
{
  if(getTemperature() >= ustawionaTemperatura)
    return false;
  else
    return true;
}

void printTemperatureAndHumidity()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(getTemperature());
  lcd.print(",  ");
  lcd.print("H: ");
  lcd.println(getHumidity());
  lcd.print("set T: ");
  lcd.print(ustawionaTemperatura);

}

void setup() {
  lcdInit();
  dhtInit();
  pinInit();

}
void termostat()
{
      if(czyWlaczacPodgrzewanie())
  {
    digitalWrite(WLACZNIKPODGRZEWANIA, stanOFF);
  }
  else
  {
    digitalWrite(WLACZNIKPODGRZEWANIA, stanON);
  }
}
void ustawianieTemperatury()
{
  if(digitalRead(buttonPinTempDown) == LOW)
  {
    ustawionaTemperatura--;
    delay(100);
    return ;
  }
    if(digitalRead(buttonPinTempUp) == LOW)
  {
    ustawionaTemperatura++;
    delay(100);
    return ;
  }
  

} 

void loop()
{
  termostat();
  ustawianieTemperatury();
  printTemperatureAndHumidity();
  delay(1000);
}