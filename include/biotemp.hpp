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
extern BioTempMQTTClient mqtt;
extern TempHandler temperature_handler;

class Biotemp {
    public:
        Biotemp() {
            handler.config(temperature_handler); // config display before using it

            handler.splashScreen(cnpemLogo); 
            handler.splashScreen(LNBioLogo);
            encoder.config(MAX_ENCODER_POSITION);
            configTimer(INTERRUPT_TIME_S);
            handler.showScreenSaver();
            mqtt.mqttConfig();
            mqtt.publishConfig();
        }

        void mainLoop(){
            handler.mainLoop();
            temperature_handler.checkThreshold();
            //mqtt.publishTemp();
        }

    private:
        InputController encoder;

};

#endif