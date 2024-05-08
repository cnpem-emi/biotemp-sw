#include <Arduino.h>
#include <InputController.hpp>

#include "temphandler.hpp"

InputController encoder;

void setup() {
  encoder.config(2);
  TempHandler temp_handler; 
}

void loop() {}