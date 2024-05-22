#include "graphicalViewHandler.hpp"
/*
GraphicalViewHandler::GraphicalViewHandler(OptionsMenu menu) {
    if(&menu != NULL) {
        mainMenu = &menu;
    }
}
*/
void GraphicalViewHandler::showOptionsMenu() {
    mainMenu.showMenu();
    
}

void GraphicalViewHandler::handleKnobEvent(KnobEvent event) {
    mainMenu.handleKnobEvent(event);
}

void GraphicalViewHandler::handlePressEvent(ButtonPressEvent event) {

}
