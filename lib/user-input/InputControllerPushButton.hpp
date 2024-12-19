#ifndef __INCLUDE_INPUT_CONTROLLER_PUSHBUTTON_HPP_
#define __INCLUDE_INPUT_CONTROLLER_PUSHBUTTON_HPP_

#include <ezButton.h>
//#include "graphicalViewHandler.hpp"

#define PUSH_BUTTON_PIN 12
#define DEBOUNCE_TIME 50

extern ezButton button;

//extern GraphicalViewHandler handler;

class InputControllerPushButton {
    public:
        void configPushButton();
        bool isPressed();
        bool isReleased();
};

#endif // _INCLUDE_INPUT_CONTROLLER_PUSHBUTTON_HPP_