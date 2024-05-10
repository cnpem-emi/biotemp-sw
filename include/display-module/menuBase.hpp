#ifndef _MENUBASE_HPP_
#define _MENUBASE_HPP_

#include <vector>
#include <string>
#include <buttonEvent.hpp>
#include <displayController.hpp>

class MenuBase {
    public:
        virtual void showMenu(DisplayController display);
        virtual void handleInputEvent(ButtonEvent event);
    
    protected:
        int arrowPosition;
        String menuName;
};

#endif  // _MENUBASE_HPP_
