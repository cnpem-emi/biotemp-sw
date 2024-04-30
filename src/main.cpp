#include <Arduino.h>
#define LED_PIN 26
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(1000); 
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
