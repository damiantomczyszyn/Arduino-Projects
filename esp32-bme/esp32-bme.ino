
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <DHT.h>
#include <WiFi.h>



const char* ssid     = "";
const char* password = "";


String getWeather();



/*#include <SPI.h>
#define BME_SCK 14
#define BME_MISO 12
#define BME_MOSI 13
#define BME_CS 15*/

#define DHTTYPE    DHT22 
#define DHTPIN 2

DHT dht(DHTPIN, DHTTYPE);


float t = 0.0;
float h = 0.0;

void printValues();

int val = 0 ;


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

unsigned long delayTime;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 test"));
  dht.begin();       
  bool status;

  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();



// wifi part:
 Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
  
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
String header;

void loop() { 
  printValues();
  //delay(delayTime);
 WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
          }
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("</head>");
           
            client.println("<body><h1>ESP32 Web Server</h1>");
            client.println("</body></html>");
            client.println();
            

    
          }
      }
    }
  }
}




void printValues() {
 
Serial.println(getWeather());  
Serial.println("**************************************************");
Serial.println();


 
}

String getWeather(){
  String weatherS="";
  weatherS+="Temperature = ";
  weatherS+=bme.readTemperature();
  weatherS+=" *C";
    
  weatherS+="Pressure = ";
  weatherS+=bme.readPressure() / 100.0F;
  weatherS+=" hPa";

  weatherS+="Approx. Altitude = ";
  weatherS+=bme.readAltitude(SEALEVELPRESSURE_HPA);
  weatherS+=" m";

  weatherS+="Humidity = ";
  weatherS+=bme.readHumidity();
  weatherS+=" %";

  weatherS+="\n";

  val=analogRead(A0); // Water Level Sensor output pin connected A0
  weatherS+="water lewel = ";  // See the Value In Serial Monitor
  weatherS+=val;  // See the Value In Serial Monitor
  weatherS+="\n";


h = dht.readHumidity();
  weatherS+="Humidity = ";
if (isnan(h)) {
   weatherS+="err";
}
else {
   weatherS+=h;
}


t = dht.readTemperature();
weatherS+="temperature = ";
if (isnan(t)) {
   weatherS+="err";
}
else {
  weatherS+=t;
}


  
return weatherS;
}
