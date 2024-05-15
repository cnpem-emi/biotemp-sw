#include <tempMenu.hpp>

void TempMenu::showMenu(DisplayController display) {
    display.clearDisplay();
    display.showMenuTitle(menuName);
    display.createMenu(itemsList);
}

void TempMenu::handleInputEvent(ButtonEvent event) {
    /*!
        @todo Criar eventos de acordo com a interface com o encoder.
    */
   Serial.println("");
}

void TempMenu::setMode(Modes mode) {
    currentMode = mode;
}

void TempMenu::setThreshold(float new_threshold) {
    currentThreshold = new_threshold;
}