#include "InputController.hpp"

GraphicalViewHandler handler;
InputController encoder;

void setup() {
  Serial.begin(9600);
  handler.config();
  encoder.config(2);
}

void loop() {
  handler.showOptionsMenu();
}
