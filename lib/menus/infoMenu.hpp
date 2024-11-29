#ifndef _INFOMENU_HPP_
#define _INFOMENU_HPP_

#include <map>

#include "menuBase.hpp"
//#include "displayController.hpp" //coloquei direto no graphicalviewhandler
#include "temphandler.hpp"
#include "biotempMQTTClient.hpp"

class InfoMenu : public MenuBase{
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