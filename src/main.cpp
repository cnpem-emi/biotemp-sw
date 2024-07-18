#include "biotemp.hpp"
#include "eventTimer.hpp"

#define MAX_ENCODER_POSITION 3
#define INTERRUPT_TIME_S 5

InputController encoder;
extern GraphicalViewHandler handler;
TempHandler temperature_handler;
BioTempMQTTClient mqtt{temperature_handler};

void setup() {
  Serial.begin(9600);
  handler.config(temperature_handler); // config display before using it

  temperature_handler.addNTCSensor(NTC_ID_1, NTC_PIN_1);

  handler.splashScreen(cnpemLogo); 
  handler.splashScreen(LNBioLogo);
  encoder.config(MAX_ENCODER_POSITION);
  configTimer(INTERRUPT_TIME_S);
  handler.showScreenSaver();
  //mqtt.mqttConfig();
  //mqtt.publishConfig();
}

void loop() {
  handler.mainLoop();
  //temperature_handler.checkThreshold();
  //mqtt.publishTemp();
}