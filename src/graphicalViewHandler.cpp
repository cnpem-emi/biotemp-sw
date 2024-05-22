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
}

void GraphicalViewHandler::config() {
    oled.displayConfig();

}
