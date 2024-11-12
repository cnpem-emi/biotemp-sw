#include "infoMenu.hpp"

InfoMenu::InfoMenu(DisplayController display_controller, 
                   TempHandler* &temperatureHandler,
                   BioTempMQTTClient* &mqtt_client) 
                   : tempHandler{temperatureHandler}, mqttClient{mqtt_client} {
    disp = &display_controller;
}

void InfoMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);

    // Automatically checks sensor health or mqtt connection health without need
    // to click in it
    if(currentOption != SILENCE_BUZZER){
        optionValue = handleOptionValue(currentOption);
    }

    disp->createMenu(option2str[currentOption], optionValue);

    // Draw arrow at the beginning
    disp->eraseArrow();
    disp->drawArrow(FIRST_ITEM_POS - 1);
}

void InfoMenu::updateMenu(int newArrowPosition){
    disp->eraseArrow();
    arrowPosition = newArrowPosition;
    disp->drawArrow(arrowPosition);
}

void InfoMenu::handleKnobEvent(KnobEvent event) {
    if (event.isScreenSaverOn == true){
        showMenu();
    }
    else {
        arrowPosition = (arrowPosition + 1) % RETURN_POS;
        updateMenu(event.position - 1);
    }
}

void InfoMenu::handlePressEvent(ButtonPressEvent event) {

    switch(event.position){   
        case FIRST_ITEM_POS:
            currentOption = SettingsOptions (((int) currentOption + 1) % OPTIONS_NUM);


            optionValue = option2Value[currentOption];

            showMenu();
            break;

        case SECOND_ITEM_POS:
            optionValue = handleOptionValue(currentOption);
            
            option2Value[currentOption] = 
            (optionValue != "" )? option2Value[currentOption] : optionValue;

            
            option2Value[currentOption] = 
            (optionValue != "" )? option2Value[currentOption] : optionValue;

            showMenu();
            updateMenu(SECOND_ITEM_POS-1);
            break;
        
        case RETURN_POS:
            returnMenu->showMenu();
            break;

        default:
            currentOption = SettingsOptions (((int) currentOption + 1) % OPTIONS_NUM);
            optionValue = option2Value[currentOption];
            showMenu();
            break;
    }
    
}

std::string InfoMenu::handleOptionValue(SettingsOptions option) {
    bool isBuzzerEnabled = false;
    switch (option){
        case MAC_ADRESS:
            return mqttClient->isConnected()? mqttClient->getMAC().c_str(): "No MAC"; 
            break;
    
        case SILENCE_BUZZER:
            isBuzzerEnabled = tempHandler->buzzer.isEnabled;
            tempHandler->buzzer.toggle(!isBuzzerEnabled);
            return !isBuzzerEnabled? "Buzzer On" : "Buzzer Off";
            break;

        case MQTT_CONNECTION_HEALTH:
            return mqttClient->isConnected()? "Connected" : "Not Connected";   
            break;

        case SENSOR_HEALTH:
            return tempHandler->getSensorsHealth()? "Healthy" : "Not Healthy";
            break;

        default:
            return "";
            break;
    }
}

void InfoMenu::showScreenMAC() {
    disp->clearDisplay();
    disp->displayText("MAC ADDR:", 1, false, 2);
    std::string macAddress;
    macAddress = mqttClient->getMacColon().c_str();
    disp->displayText(macAddress, 1, true, 2, 1);
}
