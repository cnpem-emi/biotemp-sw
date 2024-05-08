#ifndef TEST_MENU_HPP
#define TEST_MENU_HPP

#include <string>

#include "menubase.hpp"

class TestMenu : public MenuBase {
    public:
        TestMenu(DisplayController& display_controller,
                 std::string menu_name, 
                 int arrow_position);

        void showMenu() override;
        void handleInputEvent(InputEvent& event) override;

        bool testBuzzer();
        bool testWIfI();
};

#endif