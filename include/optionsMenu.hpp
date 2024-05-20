#ifndef _OPTIONSMENU_HPP_
#define _OPTIONSMENU_HPP_

#include <menuBase.hpp>

class OptionsMenu : public MenuBase{
    public:
        OptionsMenu(DisplayController display_controller, InputController input);
        bool activeMenu = false;

        void showMenu() override;

        void handleKnobEvent() override;

        void handlePressEvent() override;

    private:
        int arrowPosition;
        String menuName = "Options Menu"; 
        std::vector<std::string> menuList = {"Menu 1", "Menu 2", "Menu 3"};
        DisplayController* disp;
        InputController* encoder;
        String pointedMenu;

        void callMenu();
};



#endif  // _OPTIONSMENU_HPP_
