#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

const char* ssid     = "";     // your network SSID (name of wifi network)
const char* password = ""; // your network password

const char*  server = "weather.visualcrossing.com";  // Server URL

WiFiClientSecure client;

unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

String jsonBuffer;



void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);

  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    // wait 1 second for re-trying
    delay(1000);
}

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("\nStarting connection to server...");
  client.setInsecure();//skip verification
  if (!client.connect(server, 443))
    Serial.println("Connection failed!");
  else {
    Serial.println("Connected to server!");
    // Make a HTTP request:
    client.println("GET https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/lublin/2024-01-11/2024-01-12?unitGroup=metric&elements=datetime%2CdatetimeEpoch%2Ctempmin%2Ctemp%2Cfeelslikemax%2Chumidity%2Cpressure&include=days%2Cfcst&key=&contentType=json HTTP/1.0");
    client.println("Host: weather.visualcrossing.com");
    client.println("Connection: close");
    client.println();

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }

    client.stop();
  }
}

void loop() {
  // do nothing
}
