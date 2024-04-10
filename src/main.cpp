#include <temphandler.hpp>

#define NTC_ID 1

float temp;
SensorNTC s1;

void setup() {
  Serial.begin(9600);
  s1.enableNTC();
}

void loop() {
  temp = s1.getTemperature(NTC_ID);
  Serial.print("Temperatura: ");
  Serial.println(temp);
  delay(200);
}