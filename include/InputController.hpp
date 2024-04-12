#ifndef _INCLUDE_INPUTCONTROLLER_HPP_
#define _INCLUDE_INPUTCONTROLLER_HPP_

//INCLUDES
#include <cstdint>
#include <ezButton.h>

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
        uint8_t encoder_position; // Position of the encoder
       
        // Verify if the button was pressed
        bool isPressed();
        // Restart the counter. Use every time when enters a menu
        void restart_counter();

        InputController(); 

        // Pass the value of the position to "encoder_position" variable
        void encoderPosition();

    private:

        ezButton button = ezButton(SW_PIN);
};

// Interrupt function
void IRAM_ATTR ISR_encoder();

#endif // _INCLUDE_INPUTCONTROLLER_HPP_
