/**
 * @file InputEvent.hpp
 * @brief This is the file we keep the user input 
 * related event abstraction types.
 */
#ifndef _INCLUDE_INPUTEVENT_HPP_
#define _INCLUDE_INPUTEVENT_HPP_

typedef struct {
    int position;
    bool isScreenSaverOn;
} PushButtonEvent;

typedef struct {
    bool pressed;
    bool isScreenSaverOn;
} PushButtonPressEvent;


#endif // _INPUTEVENT_HPP_
