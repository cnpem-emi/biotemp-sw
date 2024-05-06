#include <biotempMQTTClient.hpp>

BioTempMQTTClient biotemp;

void setup() {
  Serial.begin(9600);
  biotemp.mqttConfig();
}

void loop() {
  Serial.println(biotemp.getIP());
  Serial.println(biotemp.getMAC());
  
  biotemp.publish("test", "Hello World!");

  delay(1000);
}
