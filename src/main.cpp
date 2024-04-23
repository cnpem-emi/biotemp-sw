#include <wifi.hpp>

WiFiConnection wifi;

void setup() {
  Serial.begin(9600);
  wifi.config();

}

void loop() {
  Serial.println(wifi.getIP());
  delay(1000);
}
