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

        void showOptionsMenu();

        void handleKnobEvent(KnobEvent event);
        void handlePressEvent(ButtonPressEvent event);

        void config(TempHandler& tempHandler, BioTempMQTTClient& mqttClient);

        void splashScreen(const unsigned char Logo[]);

        void showScreenSaver();

        void updateScreenSaver();

        void mainLoop();

        void addTempHandler(TempHandler& temperatureHandler){ tempHandler = &temperatureHandler;};

        void addMQTTClient(BioTempMQTTClient& mqtt_client){mqttClient = &mqtt_client;};

    private:
        DisplayController oled;
        InfoMenu info = InfoMenu(oled, tempHandler, mqttClient);
        TempMenu temp = TempMenu(oled, tempHandler);
        OptionsMenu mainMenu = OptionsMenu(oled, temp, info);
        TempHandler* tempHandler;
        BioTempMQTTClient* mqttClient;
    };

#endif 
