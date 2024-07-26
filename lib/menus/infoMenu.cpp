#include "infoMenu.hpp"

InfoMenu::InfoMenu(DisplayController display_controller, 
                   TempHandler* &temperatureHandler, 
                   BioTempMQTTClient* &mqttClient)
                   : tempHandler{temperatureHandler}, mqttClient{mqttClient} {
    disp = &display_controller;
    // converts arduino strings to cpp string
    macAddress = mqttClient->getMAC().c_str();
}

void InfoMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);
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
            option2Value[currentOption] = optionValue;
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
            return macAddress; 
            break;
    
        case SILENCE_BUZZER:
            isBuzzerEnabled = tempHandler->buzzer.isEnabled;
            tempHandler->buzzer.toggle(!isBuzzerEnabled);
            return !isBuzzerEnabled? "Buzzer On" : "Buzzer Off";
            break;

        default:
            return "Placeholder";
            break;
    }
}