#include "inputCallbacks.hpp"

void knobCallback( long value )
{
    KnobEvent event;
    event.position = value;
    handler.userRecentlyInteracted = true;
    handler.handleKnobEvent(event);
}

// The function is designed to handle changes in the button of a rotary encoder
void buttonCallback( unsigned long duration )
{
    ButtonPressEvent event;
    event.pressed = true;
    handler.userRecentlyInteracted = true;
    handler.handlePressEvent(event);
}
