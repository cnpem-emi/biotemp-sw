#ifndef _MENUBASE_HPP_
#define _MENUBASE_HPP_

#include <vector>
#include <string>
#include "displayController.hpp"
#include "InputEvent.hpp"
#include "InputController.hpp"

class MenuBase {
    public:
        bool activeMenu;
        virtual void showMenu() = 0;
        virtual void handleKnobEvent(long value) = 0;
        virtual void handlePressEvent(ButtonPressEvent event) = 0;

    protected:
        int arrowPosition;
        String menuName;
};

#endif  // _MENUBASE_HPP_
