#ifndef MENU_BASE_HPP
#define MENU_BASE_HPP

#include <string>

#include "inputEvent.hpp"

class MenuBase {
public:

    std::string menu_name;
    int arrow_position;

    // Virtual methods
    virtual void showMenu() = 0;
    virtual void handleInputEvent(InputEvent& event) = 0;
};

#endif // MENU_BASE_HPP
