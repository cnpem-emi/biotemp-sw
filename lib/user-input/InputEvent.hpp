#ifndef _INCLUDE_INPUTEVENT_HPP_
#define _INCLUDE_INPUTEVENT_HPP_

typedef struct {
    int position;
    bool isScreenSaverOn;
} KnobEvent;

typedef struct {
    bool pressed;
    bool isScreenSaverOn;
    int position;
} ButtonPressEvent;

#endif // _INCLUDE_INPUTEVENT_HPP_
