#include <WiFi.h>
#include <WebServer.h>

const char *ssid = "espB";        // Nazwa sieci Wi-Fi
const char *password = "bbbbbbbb"; // Hasło do sieci Wi-Fi

WebServer server(80); // Tworzenie obiektu serwera na porcie 80

void handleRoot() {
  server.send(200, "text/plain", "Hello, World!");
}

void setup() {
  Serial.begin(115200);

  // Uruchamianie sieci Wi-Fi
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Konfiguracja serwera
  server.on("/", handleRoot); // Ustawienie obsługi strony głównej
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Obsługa połączeń klientów
}
