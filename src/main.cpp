#include <wifi.hpp>

WiFiConnection wifi;

void setup() {
  Serial.begin(9600);
  wifi.config();
  wifi.configMQTT();

}

void loop() {
  wifi.mqttLoop();
  wifi.publishMessage("test", "Hello World", true);
  Serial.println(wifi.getIP());
  delay(1000);
}
