#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Upload Speed: 115200
// Flash Size: 4M(3M SPIFFS)

const char *ssid = "ssid";
const char *password = "pswd";

void setup() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  pinMode(4, INPUT_PULLUP);
  digitalWrite(4, HIGH);
}

void loop() {
  static unsigned long puls = 0;
  static unsigned long previousMillis = 0;
  
  if (digitalRead(4) == LOW) {
    puls++;
    delay(150);
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 30000) {
        String params;
        params = "puls=" + String(puls);
        HTTPClient http;
        http.begin("http://192.168.0.47:8888/api/electric-data"); // specifie the address
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        http.POST(params);
        http.end();
        previousMillis = currentMillis;
        puls=0;
    }
    
}
