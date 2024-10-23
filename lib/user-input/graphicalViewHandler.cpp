#include "graphicalViewHandler.hpp"

void GraphicalViewHandler::showOptionsMenu() {
    isScreenSaverOn = false;
    mainMenu.showMenu();
}

void GraphicalViewHandler::handleKnobEvent(KnobEvent event) {
    event.isScreenSaverOn = isScreenSaverOn;

    if (isScreenSaverOn == true) {
        isScreenSaverOn = false;
    }

    // This is done to avoid multiple processing threads
    if(!isKnobEventScheduled){
        isKnobEventScheduled = true;
        scheduledKnobEvent = event;
    }

    if (tempHandler!=nullptr) {
        if (tempHandler->buzzer.isBuzzerTriggered == true) {
            tempHandler->buzzer.toggle(false);
        }
    }

}

void GraphicalViewHandler::handlePressEvent(ButtonPressEvent event) {
    event.isScreenSaverOn = isScreenSaverOn;
    if (isScreenSaverOn == true) {
        isScreenSaverOn = false;
    }

    // This is done to avoid multiple processing threads
    if(!isPressEventScheduled){
        isPressEventScheduled = true;
        scheduledPressEvent = event;
    }
    //event.pressed = false;
}

void GraphicalViewHandler::handleBuzzerDisable() {
    if(tempHandler!=nullptr) {
        tempHandler->buzzer.handleDisable();

    }
}

void GraphicalViewHandler::config(TempHandler& tempHandler, BioTempMQTTClient& mqttClient) {
    oled.displayConfig();
    addTempHandler(tempHandler);
    addMQTTClient(mqttClient);

    // Verifique os thresholds imediatamente após a configuração
    for (const SensorConfig& config : tempHandler.getSensorConfigs()) {
        if (config.sensor_id != 0) {
            tempHandler.checkThreshold(config.is_enabled, config.sensor_id, config.min_threshold, config.max_threshold);
        }
    }
}

void GraphicalViewHandler::splashScreen(const unsigned char Logo[]){
    oled.showLogo(Logo);
    delay(SPLASH_SCREEN_TIME);
    delay(SPLASH_SCREEN_TIME);
    oled.clearDisplay();
}

void GraphicalViewHandler::showScreenSaver(){
    oled.clearDisplay();
    updateScreenSaver(); 
}

void GraphicalViewHandler::updateScreenSaver() {
    oled.clearDisplay();
    //oled.showMenuTitle("BioTemp");

    if(tempHandler->available_sensors.empty()) {
        oled.showMenuTitle("BioTemp");
        oled.displayText("Please Configure", 1, true);
        oled.displayText("  Temperature Sensor", 2, false);
        return;
    }

    // index for spacing the lines
    int i = 1;

    for ( auto it = tempHandler->available_sensors.begin();
          it != tempHandler->available_sensors.end(); ++it) {
        oled.displayText((it->first), i, false);
        oled.displayText(": ", i, false);

        // Displays temperature
        if((it->second)->checkSensorHealth()){
            oled.displayText((it->second)->getTemperature(), i, false, TITLE_TEXT_SIZE);
            oled.displayText(" oC", i, false);

        }
        else{ oled.displayText("No Temp.", i, false);} 

        oled.displayText(" ", i, true);
        i++;
    }

    if(!tempHandler->isThresholdTrespassed){
        oled.displayText("Temperature OK", i, true);     
    }
    else {
        oled.displayText("Sensors Triggered", i, true);     
    }
}

void GraphicalViewHandler::onConfigReceiver() {
    // Chama checkThreshold para todos os sensores configurado
    for (const SensorConfig& config : tempHandler->getSensorConfigs()) {
        if (config.sensor_id != 0) {
            tempHandler->checkThreshold(config.is_enabled, config.sensor_id, config.min_threshold, config.max_threshold);
        }
    }
}


void GraphicalViewHandler::mainLoop(){
    bool buzzer = false;
    if (tempHandler != nullptr && !tempHandler->getSensorConfigs().empty()) {
        
        for (const SensorConfig& config : tempHandler->getSensorConfigs()) {
            if (tempHandler->checkThreshold(config.is_enabled, config.sensor_id, config.min_threshold, config.max_threshold)){buzzer = true;}
        }
    }
    if (!buzzer){tempHandler->buzzer_turn_off();}

    if( isKnobEventScheduled) { 
        if(isScreenSaverOn){
            mainMenu.showMenu(); 
            isScreenSaverOn = false;
        } else {
            mainMenu.handleKnobEvent(scheduledKnobEvent);
        }
        isKnobEventScheduled = false;
        return;
    }

    if( isPressEventScheduled) { 
        if(isScreenSaverOn){
            mainMenu.showMenu();
            isScreenSaverOn = false;
        } else {
            mainMenu.handlePressEvent(scheduledPressEvent);
        };
        
        isPressEventScheduled = false;
        return;
    }
 
    // Checks if Screen saver needs to be shown
    if (screenSaverEventScheduled == true || mainMenu.requestScreenSaver == true) 
    { 

      if(mqttClient != nullptr && mqttClient->isConfigured()) {  
        DEBUG(Serial.println("Publishing Temperature...");)
        mqttClient->publishTemp();
      }

      mainMenu.requestScreenSaver = false;
      if (isScreenSaverOn == true) {
        updateScreenSaver();
        screenSaverEventScheduled = false;
      }
      else {
       showScreenSaver();
       isScreenSaverOn = true;
      }
    }
}




