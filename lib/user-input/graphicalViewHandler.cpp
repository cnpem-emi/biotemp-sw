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

void GraphicalViewHandler::config() {
    oled.displayConfig();

}

void GraphicalViewHandler::splashScreen(const unsigned char Logo[]){
    oled.showLogo(Logo);
    delay(1000);
    oled.clearDisplay();
}

void GraphicalViewHandler::showScreenSaver(){
    oled.clearDisplay();
    oled.showMenuTitle("BioTemp");
    float temp = sensor1.getTemperature();
    oled.displayText(sensor1.getSensorID(), 1, false);
    oled.displayText(": ", 1, false);
    oled.displayText(temp, 1, false);
    oled.displayText("oC", 1, false);
}

void GraphicalViewHandler::updateScreenSaver() {
    oled.clearDisplay();
    oled.showMenuTitle("BioTemp");
    float temp = sensor1.getTemperature();
    oled.displayText(sensor1.getSensorID(), 1, false);
    oled.displayText(": ", 1, false);
    oled.displayText(temp, 1, false);
    oled.displayText("oC", 1, false);
}

void GraphicalViewHandler::mainLoop(){
    // Checks if Screen saver needs to be shown
    if (screenSaverEventScheduled == true) 
    {
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


