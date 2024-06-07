#ifndef _OPTIONSMENU_HPP_
#define _OPTIONSMENU_HPP_

#include "tempMenu.hpp"
#include "infoMenu.hpp"
#include "displayController.hpp"

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

        OptionsMenu(
            DisplayController display_controller
            //TempMenu temp,
            //InfoMenu info
            );
        
        bool activeMenu = true; // True if this menu is shown on the screen, false otherwise.
        
        // Shows the main menu containing submenus.
        void showMenu() override;
        void updateMenu(int arrowPosition); 

        void handleKnobEvent(KnobEvent event) override;

        void handlePressEvent(ButtonPressEvent event) override;

    private:
        int arrowPosition = 0; // Position of the arrow shown on screen.
        String menuName = "BioTemp";  // Title of this menu show on screen.
        std::vector<std::string> menuNamesList; // List of submenu titiles.
        //std::vector<MenuBase*> menuList; // List of the submenus objects.

        // IO controller instances
        DisplayController* disp;

        // Menu instances
        TempMenu temp_menu;
        InfoMenu info_menu;

        /**********************************************************/
        /*! 
            @todo NOT FINISHED
            @brief calls a submenu by its id.
            @param id The id of the menu to be called.
            @param event The event instance get from the encoder callback function.
        */
        /**********************************************************/
        void callMenu(int id, KnobEvent event);

        /**********************************************************/
        /*! 
            @todo NOT FINISHED
            @brief calls a submenu by its id.
            @param id The id of the menu to be called.
            @param event The event instance get from the encoder callback function.
        */
        /**********************************************************/
        void callMenu(int id, ButtonPressEvent event);
};

#endif  // _OPTIONSMENU_HPP_
