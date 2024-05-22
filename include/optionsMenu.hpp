#ifndef _OPTIONSMENU_HPP_
#define _OPTIONSMENU_HPP_

#include "tempMenu.hpp"
#include "displayController.hpp"

class OptionsMenu : public MenuBase{
    public:
        int id;

        OptionsMenu(
            DisplayController display_controller,
            TempMenu temp
            );
        
        bool activeMenu;

        void showMenu() override;

        void handleKnobEvent(KnobEvent event) override;

        void handlePressEvent(ButtonPressEvent event) override;

    private:
        int arrowPosition;
        String menuName = "Options Menu"; 
        std::vector<std::string> menuNamesList;
        std::vector<MenuBase*> menuList;

        // IO controller instances
        DisplayController* disp;

        // Menu instances
        TempMenu* temp_menu;

        void callMenu(int id, KnobEvent event);
        void callMenu(int id, ButtonPressEvent event);
};

#endif  // _OPTIONSMENU_HPP_
