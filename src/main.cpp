#include "biotemp.hpp"

Biotemp biotemp;

void setup() {
   Serial.begin(9600);
}

void loop() {
  biotemp.mainLoop();
}