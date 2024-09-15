void setup() {
  // put your setup code here, to run once:

}
int pinServo=9;
int xy=0;
void loop() {
    movePulse(xy);
    xy+=20;
    if(xy==180)
    {
      xy=0;
    }
    delay(1000);
}

void movePulse_1000(){
    Serial.print("Start movePulse_1000()\t\t");
    for (int pulseCounter=0; pulseCounter<=150; pulseCounter++){
        digitalWrite(pinServo,LOW);
        delay(20); // between pulses
        digitalWrite(pinServo,HIGH);
        delayMicroseconds(1000);
    }
    Serial.println("End movePulse_1000()");
}
void movePulse(int x){
    int del=(7*x)+500;
    for (int pulseCounter=0; pulseCounter<=50; pulseCounter++){
        digitalWrite(pinServo,HIGH);
        delayMicroseconds(del);
        digitalWrite(pinServo,LOW);
        delay(20); // between pulses
    }
}