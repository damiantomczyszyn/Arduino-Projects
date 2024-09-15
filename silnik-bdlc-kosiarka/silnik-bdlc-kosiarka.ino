#define LEWY_SILNIK 9
#define PRAWY_SILNIK 10
#define SZYBKO 200
#define WOLNO 100
#define LEWY_SILNIK_KIERUNEK 11
#define LEWY_SILNIK_KIERUNEK 12


void stop(){

}

void przod(){
  stop()
  delay(500);
  digitalWrite(LEWY_SILNIK_KIERUNEK, 0);
  digitalWrite(PRAWY_SILNIK_KIERUNEK, 1);
  analogWrite(LEWY_SILNIK, SZYBKO);
  analogWrite(PRAWY_SILNIK, SZYBKO);
  
}

void tyl(){
  stop()
  delay(500);
  digitalWrite(LEWY_SILNIK_KIERUNEK, 1);
  digitalWrite(PRAWY_SILNIK_KIERUNEK, 0);
  analogWrite(LEWY_SILNIK, SZYBKO);
  analogWrite(PRAWY_SILNIK, SZYBKO);
  
  
}

void prawo(){
  stop()
  delay(500);
  digitalWrite(LEWY_SILNIK_KIERUNEK, 0);
  digitalWrite(PRAWY_SILNIK_KIERUNEK, 0);
  analogWrite(LEWY_SILNIK, SZYBKO);
  //analogWrite(PRAWY_SILNIK, SZYBKO);
}

void lewo(){
  stop()
  delay(500);
  digitalWrite(LEWY_SILNIK_KIERUNEK, 1);
  digitalWrite(PRAWY_SILNIK_KIERUNEK, 1);
  //analogWrite(LEWY_SILNIK, SZYBKO);
  analogWrite(PRAWY_SILNIK, SZYBKO);
  
}
void podczas_jazdy_lekko_lewo(){
  stop()

  
}
void podczas_jazdy_lekko_prawo(){
  stop()

  
}

void wlacz_koszenie(){

}

void wylacz_koszenie(){
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LEWY_SILNIK, OUTPUT);
  pinMode(PRAWY_SILNIK, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(LEWY_SILNIK, 200);
  analogWrite(PRAWY_SILNIK, 200);
}


