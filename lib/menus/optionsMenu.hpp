#ifndef _OPTIONSMENU_HPP_
#define _OPTIONSMENU_HPP_

#include "tempMenu.hpp"
#include "infoMenu.hpp"
#include "displayController.hpp"

#include<memory>

#define SUBMENUS_NUM 2
#define RETURN_POS 3

enum MENU_OPTIONS {
    MAIN_MENU,
    TEMP_MENU,
    INFO_MENU,
};
/********************************************************************/
/*!
    @brief Main menu interface class. This menu has the purpose of controlling 
        the behaviour of the submenus, calling the other menus member methods indirectly.
    @param display_controller The SSD1306 display object.
    @param temp The temperature menu object.
*/
/********************************************************************/
class OptionsMenu : public MenuBase{
    public:
        int id; // Main menu id.
        bool requestScreenSaver = false;

        OptionsMenu(DisplayController display_controller);
        
        bool isScreenSaverOn = true; // True if this menu is shown on the screen, false otherwise.
        
        // Shows the main menu containing submenus.
        void showMenu() override;
        void updateMenu(int arrowPosition); 

        void handleKnobEvent(KnobEvent event) override;

        void handlePressEvent(ButtonPressEvent event) override;

    private:
        int arrowPosition = 0; // Position of the arrow shown on screen.
        String menuName = "BioTemp";  // Title of this menu show on screen.

        // Menu instances
        TempMenu temp_menu;
        InfoMenu info_menu;

        void changeCurrentlyActiveMenu(MENU_OPTIONS id);
        MenuBase* activeMenu;

        std::vector<std::string> menuNamesList; // List of submenu titles.
        //std::vector<MenuBase*> menuList; // List of the submenus objects.

        // IO controller instances
        DisplayController* disp;

};
#endif  // _OPTIONSMENU_HPP_
