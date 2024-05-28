#ifndef _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
#define _INCLUDE_GRAPHICALVIEWHANDLER_HPP_

#include "optionsMenu.hpp"
#include "InputEvent.hpp"
#include "tempMenu.hpp"
#include "splashScreen.hpp"
#include "sensorNTC.hpp"
//#include "eventTimer.hpp"
#include <esp32-hal-timer.h>

/*********************************************************/
/*!
    @brief Display Handler interface class. This class handles 
        all interactions between the encoder and the display.
*/
/*********************************************************/
class GraphicalViewHandler {
    public:
        // Shows the main menu.
        void showOptionsMenu();

        void handleKnobEvent(KnobEvent event);
        void handlePressEvent(ButtonPressEvent event);

        // Dipslay configuration abstraction.
        void config();

        void splashScreen(const unsigned char Logo[]);

        // implementada apenas para teste visual
        void defaultScreen();

    private:
        DisplayController oled;
        TempMenu temp = TempMenu(oled);
        OptionsMenu mainMenu = OptionsMenu(oled, temp);
        SensorNTC temperature = SensorNTC(1);
    };

    

#endif // _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
