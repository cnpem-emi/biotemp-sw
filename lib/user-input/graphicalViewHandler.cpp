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
    mainMenu.handleKnobEvent(event);
}

void GraphicalViewHandler::handlePressEvent(ButtonPressEvent event) {
    event.isScreenSaverOn = isScreenSaverOn;
    if (isScreenSaverOn == true) {
        isScreenSaverOn = false;
    }
    mainMenu.handlePressEvent(event);
    event.pressed = false;
}

void GraphicalViewHandler::config(TempHandler& tempHandler) {
    oled.displayConfig();
    addTempHandler(tempHandler);
}

void GraphicalViewHandler::splashScreen(const unsigned char Logo[]){
    oled.showLogo(Logo);
    delay(1000);
    oled.clearDisplay();
}

void GraphicalViewHandler::showScreenSaver(){
    oled.clearDisplay();
    updateScreenSaver(); 
}

void GraphicalViewHandler::updateScreenSaver() {
    oled.clearDisplay();
    oled.showMenuTitle("BioTemp");

    if(tempHandler->available_sensors.empty()) {
        oled.displayText("Please Configure", 1, true);
        oled.displayText("  Temperature Sensor", 2, false);
        return;
    }

    for ( auto it = tempHandler->available_sensors.begin();
          it != tempHandler->available_sensors.end(); ++it) {

        oled.displayText((it->first), 1, false);
        oled.displayText(": ", 1, false);
        oled.displayText((it->second)->getTemperature(), 2, false);
        oled.displayText("oC", 1, false); 
    }

}

void GraphicalViewHandler::mainLoop(){
    // Checks if Screen saver needs to be shown
    if (screenSaverEventScheduled == true || mainMenu.requestScreenSaver == true) 
    {
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


