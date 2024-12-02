#ifndef _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
#define _INCLUDE_GRAPHICALVIEWHANDLER_HPP_

#include "InputEvent.hpp"
#include "infoMenu.hpp"
#include "splashScreen.hpp"
#include "sensorNTC.hpp"
#include "temphandler.hpp"
#include "biotempMQTTClient.hpp"
#include "InputControllerPushButton.hpp"

#include "displayController.hpp"

#include <esp32-hal-timer.h>
#include <ArduinoJson.h>

#define SPLASH_SCREEN_TIME 2000 // in milliseconds


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

        InputControllerPushButton pushButton;

        // Display configuration abstraction.
        void config(TempHandler& tempHandler, BioTempMQTTClient& mqttClient);

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
        void addMQTTClient(BioTempMQTTClient& mqtt_client){ mqttClient = &mqtt_client;};

        void handleBuzzerDisable();

        void onConfigReceiver();

    private:
        DisplayController oled;
        InfoMenu info = InfoMenu(oled, tempHandler, mqttClient);
        TempHandler* tempHandler;
        BioTempMQTTClient* mqttClient;

        bool isPressPushButtonScheduled = false;
        PushButtonPressEvent scheduledPressPushButonEvent;

        bool isPushButtonEventScheduled = false;
        PushButtonEvent scheduledPushButtonEvent;
};

#endif 
