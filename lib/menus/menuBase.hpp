#ifndef _MENUBASE_HPP_
#define _MENUBASE_HPP_

#include <vector>
#include <string>
#include "displayController.hpp"
//#include "InputEvent.hpp"

#define FIRST_ITEM_POS 1
#define SECOND_ITEM_POS 2
#define RETURN_POS 3

class MenuBase {
    public:
        int id; // ID of the menu class.
        std::string menuName; // Name of the menu class.
        MenuBase* returnMenu; // Menu to return to 

};

#endif  // _MENUBASE_HPP_
