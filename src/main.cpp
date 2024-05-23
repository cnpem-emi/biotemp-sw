#include "biotemp.hpp"

InputController encoder;

void setup() {
  encoder.config(2);
  //TempHandler temp_handler; 
  Serial.begin(9600);
  handler.config();
  encoder.config(2);
}

void loop() {
  handler.showOptionsMenu();
}
