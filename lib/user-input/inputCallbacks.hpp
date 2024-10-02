#ifndef _INPUTCALLBACKS_HPP_
#define _INPUTCALLBACKS_HPP_

#define BUZZER_OFF_TIME_S 5

#include "graphicalViewHandler.hpp"
#include "global_instances.hpp"
// #include "eventTimer.hpp"
// #include "temphandler.hpp"
// #include "infoMenu.hpp"

void knobCallback( long value );

// The function is designed to handle changes in the button of a rotary encoder
void buttonCallback( unsigned long duration);


#endif  // _INPUTCALLBACKS_HPP_
