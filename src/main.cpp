#include <Arduino.h>
#include <InputController.hpp>

InputController encoder;

void setup() {

  encoder.restart_counter();

  // use interrupt for CLK pin is enough
  // call ISR_encoder() when CLK pin changes from LOW to HIGH
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), ISR_encoder, RISING);
}

void loop() {
  encoder.encoder_position;
  encoder.isPressed();
}