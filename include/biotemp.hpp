#ifndef _BIOTEMP_HPP_
#define _BIOTEMP_HPP_

#include "global_instances.hpp"
#include "InputController.hpp"
#include "splashScreen.hpp"
#include "biotempMQTTClient.hpp"
#include "buzzer.hpp"
#include "LED.hpp"
#include "graphicalViewHandler.hpp"
#include "eventTimer.hpp"

#define MAX_ENCODER_POSITION 3
#define INTERRUPT_TIME_S 5

// Check Global Instances for more info about this extern choice
extern GraphicalViewHandler handler;

class Biotemp {
    public:
        Biotemp() {
            // It is important to config things before using them
            handler.config(temperature_handler, mqttClient); 
            encoder.config(MAX_ENCODER_POSITION);
            configTimer(INTERRUPT_TIME_S);
        } 

        void biotempBoot(){
            // Network IOC stuff
            mqttClient.mqttConfig();
            mqttClient.publishConfig();

            // Initial Screens
            handler.splashScreen(cnpemLogo); 
            handler.splashScreen(LNBioLogo);
            handler.showScreenSaver();
        }

        void mainLoop(){
            // most of the heavy-lifting is done by the handler
            handler.mainLoop(); 
        }

    private:
        InputController encoder;
        TempHandler temperature_handler;
        BioTempMQTTClient mqttClient{temperature_handler};
};

#endif