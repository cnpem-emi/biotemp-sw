#include "infoMenu.hpp"


InfoMenu::InfoMenu(DisplayController display_controller, 
                   TempHandler* &temperatureHandler,
                   BioTempMQTTClient* &mqtt_client) 
                   : mqttClient{mqtt_client} {
    disp = &display_controller;
}

void InfoMenu::showScreenMAC() {
    disp->clearDisplay();
    disp->displayText("MAC ADDR:", 1, false, 2);
    std::string macAddress;
    macAddress = mqttClient->getMacColon().c_str();
    disp->displayText(macAddress, 1, true, 2, 1);
}
