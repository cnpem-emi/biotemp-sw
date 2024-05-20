#include <graphicalViewHandler.hpp>

GraphicalViewHandler::GraphicalViewHandler(OptionsMenu menu) {
    mainMenu = &menu;
}

void GraphicalViewHandler::showOptionsMenu() {
    mainMenu->showMenu();
    
}

void GraphicalViewHandler::config(int upperBound, KnobEvent knob, ButtonPressEvent press) {
    
}