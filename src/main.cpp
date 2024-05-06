#include <dataclient.hpp>

#define NTC1_ID 1
#define NTC2_ID 2

SensorNTC s1(NTC1_ID);
SensorNTC s2(NTC2_ID);
DataClient dc;

void setup() {
  Serial.begin(9600);
  dc.subscribe(s1);
  dc.subscribe(s2);
}

void loop() {
  Serial.println(dc.getData(s1));
  Serial.println(dc.getData(s2));
  delay(1000);
}
