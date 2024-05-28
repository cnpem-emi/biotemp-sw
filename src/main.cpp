#include "biotemp.hpp"
#include <eventTimer.hpp>

InputController encoder;
extern GraphicalViewHandler handler;

void setup() {
  //TempHandler temp_handler; 
  Serial.begin(9600);
  handler.config();
  encoder.config(2);
  configTimer(5);
  handler.splashScreen(cnpemLogo);
  handler.splashScreen(LNBioLogo);

  

}

void loop() {
  //handler.showScreenSaver();
  //handler.showOptionsMenu();

}
