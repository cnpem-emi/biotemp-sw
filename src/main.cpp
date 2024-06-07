#include "biotemp.hpp"
#include <eventTimer.hpp>

InputController encoder;
extern GraphicalViewHandler handler;

void setup() {
  //TempHandler temp_handler; 
  Serial.begin(9600);
  handler.config(); // config display before using pls
  handler.splashScreen(cnpemLogo); 
  handler.splashScreen(LNBioLogo);
  encoder.config(3);
  configTimer(5);
  handler.showScreenSaver();
}

void loop() {
  //handler.showScreenSaver();
  //handler.showOptionsMenu();
  handler.mainLoop();
}
