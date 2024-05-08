#ifndef TEMP_MENU_HPP
#define TEMP_MENU_HPP

#include <string>

#include "menubase.hpp"
#include "display.hpp"

typedef enum {
   //@TODO fill this up
   DEFAULT_MODE
} Modes;

//@TODO change this value to something that makes sense
#define DEFAULT_THRESHOLD 3.0

class TempMenu : public MenuBase {
    public:

        TempMenu(DisplayController& display_controller,
                 std::string menu_name, 
                 int arrow_position);

        float current_threshold = DEFAULT_THRESHOLD;
        Modes current_mode = DEFAULT_MODE;

        void showMenu() override;
        void handleInputEvent(InputEvent& event) override;

        bool setThreshold(float new_threshold);
        bool setMode(Modes new_mode);
};

#endif
