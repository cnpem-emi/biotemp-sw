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

extern GraphicalViewHandler handler;

class Biotemp {
    public:
        Biotemp() {
            handler.config(temperature_handler, mqttClient); // config display before using it
            encoder.config(MAX_ENCODER_POSITION);
            configTimer(INTERRUPT_TIME_S);
        } 

        void biotempBoot(){
            mqttClient.mqttConfig();
            mqttClient.publishConfig();
            handler.splashScreen(cnpemLogo); 
            handler.splashScreen(LNBioLogo);
            handler.showScreenSaver();
        }

        void mainLoop(){
            handler.mainLoop();
        }

    private:
        InputController encoder;
        TempHandler temperature_handler;
        BioTempMQTTClient mqttClient{temperature_handler};
};

#endif