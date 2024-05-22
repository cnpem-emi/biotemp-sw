#include <InputController.hpp>

/*
############################################################
#################      ROTARY ENCODER    ###################
############################################################
*/

// Global variables to encoder manipulate
//int encoderPos = 0;
//bool isPressed = false;

void InputController::config(int upperBound) {
  // This tells the library that the encoder has its own pull-up resistors
  rotaryEncoder.setEncoderType( EncoderType::HAS_PULLUP );

  // Range of values to be returned by the encoder: minimum is 1, maximum is "upperBound"
  // The third argument specifies whether turning past the minimum/maximum will
  // wrap around to the other side:
  //  - true  = turn past upperBound quantity, wrap to 1; turn past 1, wrap to upperBound
  //  - false = turn past upperBound quantity, stay on upperBound; turn past 1, stay on 1
  rotaryEncoder.setBoundaries( 1, upperBound, true );

  // The function specified here will be called every time the knob is turned
  // and the current value will be passed to it
  rotaryEncoder.onTurned( &knobCallback );

  // The function specified here will be called every time the button is pushed and
  // the duration (in milliseconds) that the button was down will be passed to it
  rotaryEncoder.onPressed( &buttonCallback );

  // This is where the inputs are configured and the interrupts get attached
  rotaryEncoder.begin();
}
