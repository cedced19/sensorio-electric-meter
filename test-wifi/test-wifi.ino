#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Upload Speed: 115200
// Flash Size: 4M(3M SPIFFS)

const char *ssid = "ssid";
const char *password = "pswd";

void setup() {
Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }
  WiFi.mode(WIFI_STA);
  pinMode(12, INPUT);
  
}

void loop() {
  static unsigned long puls = 0;
  static unsigned long previousMillis = 0;
  
  if (digitalRead(12) == LOW) {

    puls++;

    Serial.print('\n');
    Serial.print(elapsedMillis);
    Serial.print(' ');
    Serial.print(puls);

    unsigned long currentMillis = millis();
    unsigned long elapsedMillis = currentMillis - previousMillis;
    if (elapsedMillis >= 10000) {
        String params;
        params = "puls=" + String(puls);
        HTTPClient http;
        http.begin("http://192.168.0.40:8888/api/electric-data"); // specifie the address
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        http.POST(params);
        http.end();
        previousMillis = currentMillis;
        puls=0;
    }
    
    delay(150);
  }
}