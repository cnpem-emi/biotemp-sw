#include "tempMenu.hpp"

TempMenu::TempMenu(DisplayController display_controller){
    disp = &display_controller;
}

void TempMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);
    disp->createMenu(itemsList[0], itemsList[1]);
}

void TempMenu::updateMenu(int arrowPosition){
    disp->eraseArrow();
    disp->drawArrow(arrowPosition);
}

void TempMenu::handleKnobEvent(KnobEvent event) {
     if (event.isScreenSaverOn == true){
            showMenu();
        }
        else {
            updateMenu(event.position - 1);
        }
}

void TempMenu::handlePressEvent(ButtonPressEvent event) {
    showMenu();
}

void TempMenu::setMode(Modes mode) {
    currentMode = mode;
}

void TempMenu::setThreshold(float new_threshold) {
    currentThreshold = new_threshold;
}
