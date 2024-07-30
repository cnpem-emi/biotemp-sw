#ifndef _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
#define _INCLUDE_GRAPHICALVIEWHANDLER_HPP_

#include "optionsMenu.hpp"
#include "InputEvent.hpp"
#include "tempMenu.hpp"
#include "infoMenu.hpp"
#include "splashScreen.hpp"
#include "sensorNTC.hpp"
#include "temphandler.hpp"
#include "biotempMQTTClient.hpp"

#include <esp32-hal-timer.h>

#define SPLASH_SCREEN_TIME 1000 // in milliseconds

/*********************************************************/
/*!
    @brief Display Handler interface class. This class handles 
        all interactions between the encoder and the display.
*/
/*********************************************************/
class GraphicalViewHandler {
    public:
        bool isScreenSaverOn = true;
        bool userRecentlyInteracted = false;

        bool screenSaverEventScheduled = false;

        /** 
         * Turns off the screen saver and displays the main menu.
         */
        void showOptionsMenu();

        /** 
         * Updates the screen saver flag and then passes the event to the `mainMenu` object.
         * 
         * @param event The `event` parameter is an object of type `KnobEvent`, 
         *  contains information about the positivion update of the knob. 
         */
        void handleKnobEvent(KnobEvent event);


        /** 
         * Updates the screen saver status, handles the button press event in the main menu,
         * and resets the pressed state of the event.
         * 
         * @param event The `event` parameter is of type `ButtonPressEvent`, which contains information
         * about a button press event, such as the button that was pressed and any other underlying related information.
         */
        void handlePressEvent(ButtonPressEvent event);

        // Dipslay configuration abstraction.
        void config(TempHandler& tempHandler);

        /** 
         *  Displays a logo on the screen for a specified number of seconds 
         *  before clearing the display.
         * 
         * @param Logo The `Logo` parameter is an array of unsigned characters representing the image data of a
         * logo to be displayed on the OLED screen.
         */
        void splashScreen(const unsigned char Logo[]);

        /** 
         * Clears the display and updates the screen saver.
         */
        void showScreenSaver();

        /** 
         * Clears the display, shows the menu title, and displays a message if temperature sensors are not available.
         * 
         * @return early if there are no available sensors. It displays a message on the OLED screen saying
         * "Please Configure Temperature Sensor" and then returns without executing any further code in the
         * function.
         */
        void updateScreenSaver();

        /** 
         * The mainLoop function in the GraphicalViewHandler class checks if a screen saver needs to be shown
         * and performs related actions as the main core of the Biotemp Product. 
         */
        void mainLoop();

        void addTempHandler(TempHandler& temperatureHandler){ tempHandler = &temperatureHandler;};

    private:
        DisplayController oled;
        InfoMenu info = InfoMenu(oled, tempHandler);
        TempMenu temp = TempMenu(oled, tempHandler);
        OptionsMenu mainMenu = OptionsMenu(oled, temp, info);
        TempHandler* tempHandler;
    };

#endif 
