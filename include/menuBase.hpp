#ifndef _MENUBASE_HPP_
#define _MENUBASE_HPP_

#include <vector>
#include <string>
//#include "displayController.hpp"
#include "InputEvent.hpp"

class MenuBase {
    public:
        int id;
        bool isActive;
        std::string menuName;
        
        virtual void showMenu() = 0;
        virtual void handleKnobEvent(KnobEvent event) = 0;
        virtual void handlePressEvent(ButtonPressEvent event) = 0;

    protected:
        int arrowPosition;

};

#endif  // _MENUBASE_HPP_
