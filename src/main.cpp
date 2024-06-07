#include "biotemp.hpp"
#include <eventTimer.hpp>

InputController encoder;
extern GraphicalViewHandler handler;
#define MAX_ENCODER_POSITION 3
#define INTERRUPT_TIME_S 5

void setup() {
  //TempHandler temp_handler; 
  Serial.begin(9600);
  handler.config(); // config display before using pls
  handler.splashScreen(cnpemLogo); 
  handler.splashScreen(LNBioLogo);
  encoder.config(MAX_ENCODER_POSITION);
  configTimer(INTERRUPT_TIME_S);
  handler.showScreenSaver();
}

void loop() {
  //handler.showScreenSaver();
  //handler.showOptionsMenu();
  handler.mainLoop();
}
