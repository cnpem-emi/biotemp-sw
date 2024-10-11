#ifndef _BIOTEMP_HPP_
#define _BIOTEMP_HPP_

#include "global_instances.hpp"
#include "InputController.hpp"
#include "biotempMQTTClient.hpp"
#include "graphicalViewHandler.hpp"
#include "eventTimer.hpp"
#include "debug-config.hpp"

#define MAX_ENCODER_POSITION 3
#define INTERRUPT_TIME_S 5

// Check Global Instances for more info about this extern choice
extern GraphicalViewHandler handler;

class Biotemp {
    public:
        // IMPORTANT: only put this function into arduino setup
        void setup() {
            // It is important to config things before using them
            //handler.config(temperature_handler, mqttClient); 
            handler.config(temperature_handler, mqttClient); 
            encoder.config(MAX_ENCODER_POSITION);

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
            // most of the heavy-lifting is done by the handler
            handler.mainLoop(); 

            // IMPORTANT: this need to be refreshed frequently
            mqttClient.mqttLoop();

            if(!alreadySendConfig && mqttClient.isConnected()){
                Serial.println("Trying to Publish Config");
                mqttClient.publishConfig();
                alreadySendConfig = true;
            }

        }
        
    private:
        bool alreadySendConfig = false;
        InputController encoder;
        TempHandler temperature_handler;
        BioTempMQTTClient mqttClient{temperature_handler};
};

#endif