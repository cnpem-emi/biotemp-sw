#include "optionsMenu.hpp"
#include "tempMenu.hpp"
#include "infoMenu.hpp"
#include "testMenu.hpp"

using MenuPtr = std::unique_ptr<MenuBase>;

OptionsMenu::OptionsMenu(DisplayController& display_controller){
    // Don't do Dynamic allocation like this in small microcontrollers
    available_menus[INFO_MENU_NAME] =  MenuPtr(new InfoMenu(display_controller, 
                                                            std::string(TEST_MENU_NAME), 
                                                            DEFAULT_CURSOR_POS));

    available_menus[TEST_MENU_NAME] =  MenuPtr(new TestMenu(display_controller,
                                                            std::string(TEST_MENU_NAME), 
                                                            DEFAULT_CURSOR_POS));

    available_menus[TEMP_MENU_NAME] =  MenuPtr(new TempMenu(display_controller,
                                                            std::string(TEMP_MENU_NAME), 
                                                            DEFAULT_CURSOR_POS));
}
