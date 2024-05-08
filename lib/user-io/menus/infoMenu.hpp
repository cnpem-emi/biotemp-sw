#ifndef INFO_MENU_HPP
#define INFO_MENU_HPP

#include <string>

#include "menubase.hpp"
#include "display.hpp"

class InfoMenu : public MenuBase {
    public:
        InfoMenu(DisplayController& display_controller,
                 std::string menu_name, 
                 int arrow_position);

        std::string mac_address;
        bool registered_status;
        
        void showMenu() override;
        void handleInputEvent(InputEvent& event) override;

        std::string getMacAdress();
        bool getRegisteredStatus();
};

#endif