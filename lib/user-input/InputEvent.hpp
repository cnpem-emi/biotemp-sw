/**
 * @file InputEvent.hpp
 * @brief This is the file we keep the user input 
 * related event abstraction types.
 */
#ifndef _INCLUDE_INPUTEVENT_HPP_
#define _INCLUDE_INPUTEVENT_HPP_

//------------------- ENCODER --------------
// typedef struct {
//     int position;
//     bool isScreenSaverOn;
// } KnobEvent;

// typedef struct {
//     bool pressed;
//     bool isScreenSaverOn;
//     int position;
// } ButtonPressEvent;

//------------------- PB --------------
typedef struct {
    int position;
    bool isScreenSaverOn;
} PushButtonEvent;

typedef struct {
    bool pressed;
    bool isScreenSaverOn;
    int position;
} PushButtonPressEvent;


#endif 
