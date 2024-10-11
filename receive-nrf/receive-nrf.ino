
#include "RF24.h"

RF24 radio(9,10);
long weight;

void setup(void) {

 delay(1000);
 Serial.begin(9600);
 Serial.println("Setup");
 radio.begin();
 radio.setChannel(5);
 radio.setDataRate(RF24_1MBPS);
 radio.setPALevel(RF24_PA_LOW);
 radio.openReadingPipe(1, 0x1234567890LL);
 radio.startListening();
}
void loop(void) {
  if(radio.available()){
    radio.read(&weight, sizeof(weight));
    Serial.println(weight);
  }
}