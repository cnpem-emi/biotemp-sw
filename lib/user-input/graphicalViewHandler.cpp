#include "graphicalViewHandler.hpp"

void GraphicalViewHandler::showOptionsMenu() {
    isScreenSaverOn = false;
    mainMenu.showMenu();
}

void GraphicalViewHandler::handleKnobEvent(KnobEvent event) {
    Serial.println(event.position);
    mainMenu.handleKnobEvent(event);
}

void GraphicalViewHandler::handlePressEvent(ButtonPressEvent event) {
    if (isScreenSaverOn == true) {
        isScreenSaverOn = false;
        mainMenu.handlePressEvent(event);
        Serial.println("ScreenSaver = true");
    } else {
        Serial.println("ScreenSaver = false");
    }
    
    // estrutura para teste visual
    // apagar depois
    /*
    if (mainMenu.activeMenu == true) {
        Serial.print("menu não ativo");
    } else {
        mainMenu.activeMenu = true;
        showOptionsMenu();
    }
    */
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
    float temp = temperature.getTemperature();
    oled.displayText("Temperatura: ", 1, false);
    oled.displayText(temp, 1, false);
    oled.displayText(" oC", 1, false);
    //oled.clearDisplay();
    //oled.eraseText();
}

void GraphicalViewHandler::updateScreenSaver() {
    float temp = temperature.getTemperature();
    

}
