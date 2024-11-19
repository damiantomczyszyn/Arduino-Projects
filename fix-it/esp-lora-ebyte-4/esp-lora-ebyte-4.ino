https://wolles-elektronikkiste.de/en/using-lora-with-the-ebyte-e220-e22-and-e32-series

#include "LoRa_E220.h"
#include <HardwareSerial.h>
HardwareSerial LoRaSerial(2);
LoRa_E220 e220ttl(&LoRaSerial, 3, 7, 6); // AUX M0 M1
 
void setup() {
  Serial.begin(9600);
  delay(500);
 
  Serial.println("Hi, I'm going to send message!");
 
  // Startup all pins and UARTD
  e220ttl.begin();
 
  // Send message
  ResponseStatus rs = e220ttl.sendMessage("Hello, world?");
  // Check if there is some problem of successfully send
  Serial.println(rs.getResponseDescription());
}
 
void loop() {
    // If something available
  if (e220ttl.available()>1) {
      // read the String message
    ResponseContainer rc = e220ttl.receiveMessage();
    // Is something goes wrong print error
    if (rc.status.code!=1){
        Serial.println(rc.status.getResponseDescription());
    }else{
        // Print the data received
        Serial.println(rc.data);
    }
  }
  if (Serial.available()) {
      String input = Serial.readString();
      e220ttl.sendMessage(input);
  }
}