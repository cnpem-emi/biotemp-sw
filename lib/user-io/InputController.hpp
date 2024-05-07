#ifndef _INCLUDE_INPUTCONTROLLER_HPP_
#define _INCLUDE_INPUTCONTROLLER_HPP_

//INCLUDES
#include <ESP32RotaryEncoder.h>

#define CLK_PIN 25  // PIN ESP32 S2 WEMOS -> 12
#define DT_PIN 26   // PIN ESP32 S2 WEMOS -> 6
#define SW_PIN 27   // PIN ESP32 S2 WEMOS -> 34

#define DIRECTION_CW 0   // clockwise direction
#define DIRECTION_CCW 1  // counter-clockwise direction

/*****************************************************/
/*!
    @brief Rotary encoder interface class.
*/
/*****************************************************/
class InputController{
    public:
        void config(int upperBound);

    private:
        RotaryEncoder rotaryEncoder = RotaryEncoder(CLK_PIN, DT_PIN, SW_PIN);
};

void knobCallback( long value );
void buttonCallback( unsigned long duration );

#endif // _INCLUDE_INPUTCONTROLLER_HPP_