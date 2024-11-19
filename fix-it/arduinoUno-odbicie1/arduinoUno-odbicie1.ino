   /*
  Piezoelectric-Shock-Tap-Sensor-Vibration-Switch-Module
  made on 05 Jan 2021
  by Amir Mohammad Shojaee @ Electropeak
  Home
https://electropeak.com/learn/interfacing-piezoelectric-vibration-shock-tap-sensor-with-arduino/
*/

#define Dig_pin 2
int Dig_out = LOW;
int Ana_out = 0;
 
void setup() {
   Serial.begin(9600);
   pinMode(Dig_pin, INPUT);
   pinMode(A0, INPUT);
}
 
void loop() {
   Dig_out = digitalRead(Dig_pin)*100;
   Ana_out = analogRead(A0);
  // Serial.print("Anaolog : ");
   Serial.print(Ana_out);

   Serial.print("\t"); // Tabulator dla oddzielenia etykiet
   //Serial.print("       Digital :");
   Serial.println(Dig_out);
   
}
