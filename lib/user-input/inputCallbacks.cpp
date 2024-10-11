#include "inputCallbacks.hpp"

/**
 * The function `knobCallback` creates a KnobEvent with the position set
 * to the input value and sets a flag indicating recent user interaction.
 * Then handles the knobEvent with a handler.
 * 
 * @param value The `value` parameter in the `knobCallback` function represents the position of a knob
 * or dial that has been adjusted by the user.
 */
void knobCallback( long value )
{
    KnobEvent event;
    event.position = value;
    handler.userRecentlyInteracted = true;
    handler.handleKnobEvent(event);
    
}

/**
 * The function `buttonCallback` notifies a handler with the event information.
 * 
 * @param duration necessary for the boilerplate of the callback, but not used in this context
 */
void buttonCallback( unsigned long duration )
{
    ButtonPressEvent event;
    event.pressed = true;
    handler.userRecentlyInteracted = true;
    handler.handlePressEvent(event);
}
