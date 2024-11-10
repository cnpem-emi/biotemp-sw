#ifndef _INFOMENU_HPP_
#define _INFOMENU_HPP_

#include <map>

#include "menuBase.hpp"
#include "displayController.hpp"
#include "temphandler.hpp"
#include "biotempMQTTClient.hpp"

#define OPTIONS_NUM 4 // number of options
typedef enum {
    MAC_ADRESS,
    SILENCE_BUZZER,
    SENSOR_HEALTH,
    MQTT_CONNECTION_HEALTH
} SettingsOptions;

#define OPTION_IDX 0
#define VALUE_IDX 1

class InfoMenu : public MenuBase{
    public:
        int id;
        String menuName = "Settings";

        /*InfoMenu(DisplayController display_controller, 
                 TempHandler* &temperatureHandler,
                 BioTempMQTTClient* &mqttClient);
        */

        InfoMenu(DisplayController display_controller, 
                 TempHandler* &temperatureHandler,
                 BioTempMQTTClient* &mqtt_client);

        void showMenu() override;
        void updateMenu(int arrowPosition);
        void handleKnobEvent(KnobEvent event) override;
        void handlePressEvent(ButtonPressEvent event) override;

        void showScreenMAC();

        bool espRegisteredStatus = false;

    private:
        uint8_t arrowPosition = 1;
        DisplayController* disp;
        //BioTempMQTTClient* mqttClient;

        SettingsOptions currentOption = MAC_ADRESS;

        std::string macAddress = "No MAC";

        std::string optionValue = macAddress;

        std::map<SettingsOptions, std::string> option2str = {{MAC_ADRESS,"Mac Addr."},
                                                             {SILENCE_BUZZER, "Silence Buzzer"},
                                                             {SENSOR_HEALTH, "Sensor Health"},
                                                             {MQTT_CONNECTION_HEALTH, "Connection Health"}};

        std::map<SettingsOptions, std::string> option2Value = {{MAC_ADRESS, macAddress},
                                                                {SILENCE_BUZZER, "Buzzer On"},
                                                                {SENSOR_HEALTH, "No Data"},
                                                                {MQTT_CONNECTION_HEALTH, "No Data"}};;

        std::string handleOptionValue(SettingsOptions option);
        TempHandler* &tempHandler;
        BioTempMQTTClient* &mqttClient;

};

#endif  // _INFOMENU_HPP_