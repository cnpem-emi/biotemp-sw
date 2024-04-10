#include <temphandler.hpp>

#define NTC_ID 1

SensorNTC s1(NTC_ID);

float temp;
std::string id;

void setup() {
  Serial.begin(9600);
  s1.enableNTC();
  id = s1.sensorID;
}

void loop() {
  temp = s1.getTemperature();
  Serial.println(id.c_str());
  Serial.print("Temperatura: ");
  Serial.println(temp);
  delay(200);
}
