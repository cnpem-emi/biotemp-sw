#include "graphicalViewHandler.hpp"

void GraphicalViewHandler::showOptionsMenu() {
    mainMenu.showMenu();
    
}

void GraphicalViewHandler::handleKnobEvent(KnobEvent event) {
    Serial.println(event.position);
    mainMenu.handleKnobEvent(event);
}

void GraphicalViewHandler::handlePressEvent(ButtonPressEvent event) {
    Serial.println(event.pressed);
    mainMenu.handlePressEvent(event);
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
    delay(4000);
    oled.clearDisplay();
}

void GraphicalViewHandler::defaultScreen(){
    float temp = temperature.getTemperature();
    oled.displayText("Temperatura: ", 1, false);
    oled.displayText(temp, 1, false);
    oled.displayText(" oC", 1, false);
    oled.clearDisplay();
    //oled.eraseText();
}
