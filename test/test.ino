void setup() {
  Serial.begin(115200);

  pinMode(12, INPUT);
}

void loop() {
  static unsigned long puls = 0;
  static unsigned long previousMillis = 0;
  
  if (digitalRead(12) == LOW) {

    puls++;

    unsigned long currentMillis = millis();
    unsigned long elapsedMillis = currentMillis - previousMillis;
    if (elapsedMillis >= 10000) {
        Serial.print('\n');
        Serial.print(elapsedMillis);
        Serial.print(' ');
        Serial.print(puls);
        previousMillis = currentMillis;
        puls=0;
    }
    
    delay(150);
  }
}
