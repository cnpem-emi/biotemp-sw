#ifndef _INFOMENU_HPP_
#define _INFOMENU_HPP_

#include <map>

#include "displayController.hpp"
#include "temphandler.hpp"
#include "biotempMQTTClient.hpp"

class InfoMenu {
    public:
        InfoMenu(DisplayController display_controller, 
                 TempHandler* &temperatureHandler,
                 BioTempMQTTClient* &mqtt_client);

        void showScreenMAC();

    private:
        DisplayController* disp;
        BioTempMQTTClient* &mqttClient;
};

#endif  // _INFOMENU_HPP_