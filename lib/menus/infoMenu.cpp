#include "infoMenu.hpp"

InfoMenu::InfoMenu(DisplayController display_controller){
    disp = &display_controller;
}

void InfoMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);
    disp->createMenu(itemsList[0], itemsList[1]);
    disp->drawArrow(RETURN_POS - 1);
}

void InfoMenu::updateMenu(int arrowPosition){
    disp->eraseArrow();
    disp->drawArrow(arrowPosition);
}

void InfoMenu::handleKnobEvent(KnobEvent event) {
     if (event.isScreenSaverOn == true){
            showMenu();
        }
}

void InfoMenu::handlePressEvent(ButtonPressEvent event) {
    returnMenu->showMenu();
}