    /*
  SW-18010P-Vibration-Sensor-Module
  made on 05 Jan 2021
  by Amir Mohammad Shojaee @ Electropeak
  Home
https://electropeak.com/learn/interfacing-sw-18010p-vibration-sensor-module-with-arduino/
*/

#define Dig_pin 7
int Dig_out = LOW;
int Ana_out = 1;
 
void setup() {
   Serial.begin(9600);
}
 
void loop() {
   Dig_out = digitalRead(Dig_pin);
   Dig_out = Dig_out*10;
   Ana_out = analogRead(A0);
  // Serial.print("Anaolog : ");
   Serial.print(Ana_out);
   Serial.print("\t");
   //Serial.print("          Digital :");
   Serial.println(Dig_out);
   delay(500);
}
