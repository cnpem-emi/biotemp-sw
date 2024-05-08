#ifndef OPTIONS_MENU_HPP 
#define OPTIONS_MENU_HPP 

#include <map>
#include <string>
#include <memory>

#include "menubase.hpp"
#include "inputEvent.hpp"
#include "display.hpp"

#define TEMP_MENU_NAME "TempMenu"
#define INFO_MENU_NAME "InfoMenu"
#define TEST_MENU_NAME "TestMenu"

#define DEFAULT_CURSOR_POS 0

class OptionsMenu : public MenuBase {
    public:
        OptionsMenu(DisplayController& display_controller);
        
        // @TODO do this with enums or something
        std::map<std::string, std::unique_ptr<MenuBase>> available_menus;

        void callMenu(std::string menu_name, InputEvent& event);

        void showMenu() override;
        void handleInputEvent(InputEvent& event) override;
};

#endif 