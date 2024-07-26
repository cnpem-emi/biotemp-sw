#ifndef _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
#define _INCLUDE_GRAPHICALVIEWHANDLER_HPP_

#include "optionsMenu.hpp"
#include "InputEvent.hpp"
#include "tempMenu.hpp"
#include "infoMenu.hpp"
#include "splashScreen.hpp"
#include "sensorNTC.hpp"
#include "temphandler.hpp"
//#include "eventTimer.hpp"
#include <esp32-hal-timer.h>
#include "biotempMQTTClient.hpp"

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
        //bool inputEventScheduled = false;

        // Shows the main menu.
        void showOptionsMenu();

        void handleKnobEvent(KnobEvent event);
        void handlePressEvent(ButtonPressEvent event);

        // Dipslay configuration abstraction.
        void config(TempHandler& tempHandler, BioTempMQTTClient& mqttClient);

        void splashScreen(const unsigned char Logo[]);

        // implementada apenas para teste visual
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

    

#endif // _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
