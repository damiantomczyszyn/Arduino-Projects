#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9,10);
long weight;

void setup(void) {


 radio.begin();
 radio.setChannel(5);
 radio.setDataRate(RF24_1MBPS);
 radio.setPALevel(RF24_PA_LOW);
 radio.openWritingPipe(0x1234567890LL);
 radio.stopListening();
 
}
void loop(void) {
weight=13381;
radio.write(&weight,sizeof(weight));
delay(1000);
}