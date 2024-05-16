#include <tempMenu.hpp>

TempMenu::TempMenu(DisplayController display_controller, InputController input){
    disp = &display_controller;
    encoder = &input;
}

void TempMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);
    disp->createMenu(itemsList);
}

void TempMenu::handleKnobEvent(KnobEvent event) {
    //!@todo Criar evento
}

void TempMenu::handlePressEvent(ButtonPressEvent event) {
    //!@todo Criar evento
}

void TempMenu::setMode(Modes mode) {
    currentMode = mode;
}

void TempMenu::setThreshold(float new_threshold) {
    currentThreshold = new_threshold;
}
