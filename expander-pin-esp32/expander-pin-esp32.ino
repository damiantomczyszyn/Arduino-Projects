#include <PCF8575.h> //https://github.com/xreef/PCF8575_library/archive/master.zip
#include <Wire.h>

//https://www.instructables.com/PCF8575-i2c-16-Pins-Digital-IO-Expander-Fast-Easy-/

// Set dht12 i2c comunication with second Wire using 21 22 as SDA SCL

// Instantiate Wire for generic use at 100kHz
//TwoWire I2Ctwo = TwoWire(1);
 
// Set dht12 i2c comunication with second Wire using 21 22 as SDA SCL

PCF8575 pcf8575(0x20, 19,22);

void setup() {

  Serial.begin(115200);
  delay(1000);
  pcf8575.begin();
  for(int i=0;i<16;i++){
    pcf8575.pinMode(i, OUTPUT);
  }

  for(int i=0;i<16;i++){
    pcf8575.digitalWrite(i, LOW);
    
  }
  Serial.println("LOW");

  delay(8000);

  for(int i=0;i<16;i++){
    pcf8575.digitalWrite(i, HIGH);
  }
   Serial.println("HIGH");
   delay(8000);
   
  //PCF8575::DigitalInput di = PCF8575.digitalReadAll();
/*	Serial.print("READ VALUE FROM PCF P1: ");
	Serial.print(di.p0);
	Serial.print(" - ");
	Serial.print(di.p1);
	Serial.print(" - ");
	Serial.print(di.p2);
	Serial.print(" - ");
	Serial.println(di.p3);
*/
 // int p1Digital = pcf8575.digitalRead(P1); // read P1
 // PCF8575.digitalWrite(P1, LOW);//write
}



void loop() {
  // put your main code here, to run repeatedly:
    for(int i=0;i<16;i++){
    pcf8575.digitalWrite(i, HIGH);
    delay(1000);
  }
  delay(1000);
      for(int i=0;i<16;i++){
    pcf8575.digitalWrite(i, LOW);
    delay(1000);
  }
  delay(1000);

}
