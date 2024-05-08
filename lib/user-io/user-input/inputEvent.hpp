#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP

#include <string>

class InputEvent {
    public:
        std::string event_id; 
        InputEvent(const std::string& id) 
        {
            event_id = id;
        }
};
#endif