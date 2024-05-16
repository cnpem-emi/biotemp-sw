#include "optionsMenu.hpp"

OptionsMenu::OptionsMenu(DisplayController display_controller, InputController input) {
    disp = &display_controller;
    encoder = &input;
    
    encoder->setCallbacks(handleKnobEvent, handlePressEvent);
}

void OptionsMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);
    disp->createMenu(menuList);
    activeMenu = true;
}

void OptionsMenu::handleKnobEvent(long value) {
    //!@todo KnobEvent, salvar o nome do menu sempre que a flecha apontar para ele
}

void OptionsMenu::handlePressEvent(ButtonPressEvent event) {
    callMenu();
}

void OptionsMenu::callMenu() {
    
  
}