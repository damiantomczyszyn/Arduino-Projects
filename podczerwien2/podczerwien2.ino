#include <IRremote.h>

const int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;

IRsend mySender;


const int greenPin = 11;


void setup(){
  irrecv.enableIRIn();
  irrecv.blink13(true);
  //pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);


  uint32_t data = 0xB24D9F60;
  uint8_t len = 32;

  mySender.sendNEC(data, len);
  
  
}
  uint32_t data = 0xB24D9F60;
  uint8_t len = 32;


void loop(){
  
    mySender.sendNEC(data, len);
    if (irrecv.decode(&results)){
      


        switch(results.value){
          case 0xB24D7B84: //Keypad button "2"
          digitalWrite(greenPin, HIGH);
          delay(2000);
          digitalWrite(greenPin, LOW);
          }
          
        switch(results.value){
          case 0xB24D9F60: //Keypad button "2"
          digitalWrite(greenPin, HIGH);
          delay(2000);
          digitalWrite(greenPin, LOW);
          }

        irrecv.resume(); 
    }
    
}