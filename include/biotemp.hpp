#ifndef _BIOTEMP_HPP_
#define _BIOTEMP_HPP_

#include "global_instances.hpp"
#include "InputControllerPushButton.hpp"
#include "biotempMQTTClient.hpp"
#include "graphicalViewHandler.hpp"
#include "eventTimer.hpp"
#include "debug-config.hpp"

#define INTERRUPT_TIME_S 3

// Check Global Instances for more info about this extern choice
extern GraphicalViewHandler handler;

class Biotemp {
    public:
        // IMPORTANT: only put this function into arduino setup
        void setup() {
            // It is important to config things before using them
            handler.config(temperature_handler, mqttClient); 
            
            pushbutton.configPushButton();

            // Network IOC stuff
            mqttClient.mqttConfig();
            configTimer(INTERRUPT_TIME_S);
        } 

        void biotempBoot(){
            // Initial Screens
            handler.splashScreen(cnpemLogo); 
            handler.splashScreen(LNBioLogo);
            handler.showScreenSaver();
        }

        void mainLoop(){
            // MUST call the loop() function first
            button.loop(); 

            // most of the heavy-lifting is done by the handler
            handler.mainLoop();

            // IMPORTANT: this need to be refreshed frequently
            mqttClient.mqttLoop();

            if(!alreadySendConfig && mqttClient.isConnected()){
                Serial.println("Trying to Publish Config");
                mqttClient.publishConfig();
                alreadySendConfig = true;
                mqttClient.configCallback();
            }

        }
        
    private:
        bool alreadySendConfig = false;
        TempHandler temperature_handler;
        BioTempMQTTClient mqttClient{temperature_handler};
        InputControllerPushButton pushbutton;
};

#endif // BIOTEMP_HPP_