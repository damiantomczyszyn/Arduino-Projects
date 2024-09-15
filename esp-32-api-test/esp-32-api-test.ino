
#include <WiFi.h>
#include <WiFiClientSecure>
#include <Arduino_JSON.h>

const char* ssid = "";
const char* password = "";


String openWeatherMapApiKey = "";



String city = "Porto";
String countryCode = "PT";


unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

String jsonBuffer;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {

  if ((millis() - lastTime) > timerDelay) {

    if(WiFi.status()== WL_CONNECTED){
      String serverPath = "https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/lublin/2024-01-11/2024-01-12?unitGroup=metric&elements=datetime%2CdatetimeEpoch%2Ctempmin%2Ctemp%2Cfeelslikemax%2Chumidity%2Cpressure&include=days%2Cfcst&key="+openWeatherMapApiKey+"&contentType=json";
      
      jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println(jsonBuffer);
      JSONVar myObject = JSON.parse(jsonBuffer);
  
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }
    
      Serial.print("JSON object = ");
      Serial.println(myObject);

    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    

  http.begin(client, serverName);
  

  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}
