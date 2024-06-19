#include "biotemp.hpp"
#include "eventTimer.hpp"

#define MAX_ENCODER_POSITION 3
#define INTERRUPT_TIME_S 5

InputController encoder;
extern GraphicalViewHandler handler;
BioTempMQTTClient mqtt;

void setup() {
  Serial.begin(115200);
  handler.config(); // config display before using it
  handler.splashScreen(cnpemLogo); 
  handler.splashScreen(LNBioLogo);
  encoder.config(MAX_ENCODER_POSITION);
  configTimer(INTERRUPT_TIME_S);
  handler.showScreenSaver();
  mqtt.mqttConfig();
}

void loop() {
  handler.mainLoop();
  mqtt.publish("test", "Hi");
}
