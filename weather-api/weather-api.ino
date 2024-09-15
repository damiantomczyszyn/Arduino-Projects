/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-open-weather-map-thingspeak-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  Code compatible with ESP8266 Boards Version 3.0.0 or above 
  (see in Tools > Boards > Boards Manager > ESP8266)
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>

const char* ssid = "";
const char* password = "";

// Your Domain name with URL path or IP address with path
String openWeatherMapApiKey = "";
// Example:

// Replace with your country code and city
String city = "Lublin";
String countryCode = "PL";

// THE DEFAULT TIMER IS SET TO 10 SECONDS FOR TESTING PURPOSES
// For a final application, check the API call limits per hour/minute to avoid getting blocked/banned
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 10 seconds (10000)
unsigned long timerDelay = 10000;

String jsonBuffer;

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() {
  delay(10000);
  // Send an HTTP GET request
  if ((millis() - lastTime) > timerDelay) {
    // Check WiFi connection status
    if (WiFi.status() == WL_CONNECTED) {
           String serverPath = "https://api.openweathermap.org/data/2.5/onecall?lat=33.44&lon=-94.04&exclude=hourly,minutely&appid=";
          jsonBuffer = httpGETRequest(serverPath.c_str());
      Serial.println("start");
      Serial.println(jsonBuffer);
      Serial.println("end");
      JSONVar myObject = JSON.parse(jsonBuffer);

      // JSON.typeof(jsonVar) can be used to get the type of the var
      if (JSON.typeof(myObject) == "undefined") {
        Serial.println("Parsing input failed!");
        return;
      }

      Serial.print("JSON object = ");
      Serial.println(myObject);

    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  // Your IP address with path or Domain name with URL path
  http.begin(client, serverName);
  http.addHeader("User-Agent", "Mozilla/5.0");
  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "";

  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();

  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
