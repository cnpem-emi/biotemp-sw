#ifndef _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
#define _INCLUDE_GRAPHICALVIEWHANDLER_HPP_

#include "optionsMenu.hpp"
#include "InputEvent.hpp"
#include "tempMenu.hpp"
//#include <inputCallbacks.hpp>


class GraphicalViewHandler {
    public:
        void showOptionsMenu();
        void handleKnobEvent(KnobEvent event);
        void handlePressEvent(ButtonPressEvent event);

    private:
        DisplayController oled;
        TempMenu temp = TempMenu(oled);
        OptionsMenu mainMenu = OptionsMenu(oled, temp);
    };

/*
inline void knobCallback( long value )
{
    KnobEvent event;
    event.position = value;
    handler.handleKnobEvent(event);
}

// The function is designed to handle changes in the button of a rotary encoder
inline void buttonCallback( unsigned long duration )
{
    ButtonPressEvent event;
    event.pressed = true;
    handler.handlePressEvent(event);
}
*/
#endif // _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
