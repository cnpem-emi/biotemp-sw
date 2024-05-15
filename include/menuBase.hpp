#ifndef _MENUBASE_HPP_
#define _MENUBASE_HPP_

#include <vector>
#include <string>
#include <buttonEvent.hpp>
#include <displayController.hpp>

class MenuBase {
    public:
        virtual void showMenu(DisplayController display) = 0;
        virtual void handleInputEvent(ButtonEvent event) = 0;

    protected:
        int arrowPosition;
        String menuName;
};

#endif  // _MENUBASE_HPP_
