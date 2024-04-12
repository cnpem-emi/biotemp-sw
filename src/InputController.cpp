#include <InputController.hpp>

/*
############################################################
#################      ROTARY ENCODER    ###################
############################################################
*/

volatile int counter = 0;
volatile int direction = DIRECTION_CW;
volatile unsigned long last_time;  // for debouncing
int prev_counter;

void InputController::encoderPosition() {
    encoder_position = counter;
  }

void InputController::restart_counter() {
  counter = 0;
}

bool InputController::isPressed(){
    
    button.loop();
    if (button.isPressed()){
      return true;
    }else{
      return false;
    }
}

InputController::InputController(){
  // configure encoder pins as inputs
  pinMode(CLK_PIN, INPUT);
  pinMode(DT_PIN, INPUT);
  button.setDebounceTime(50);  // set debounce time to 50 milliseconds

}

void IRAM_ATTR ISR_encoder() {

  if ((millis() - last_time) < 50)  // debounce time is 50ms
    return;

  if (digitalRead(DT_PIN) == HIGH) {
    // the encoder is rotating in counter-clockwise direction => decrease the counter
    counter--;
    direction = DIRECTION_CCW;
  } else {
    // the encoder is rotating in clockwise direction => increase the counter
    counter++;
    direction = DIRECTION_CW;
  }

  last_time = millis();
  uint8_t encoderPosition();
}
