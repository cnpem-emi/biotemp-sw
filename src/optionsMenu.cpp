#include "optionsMenu.hpp"

OptionsMenu::OptionsMenu(DisplayController display_controller, InputController input) {
    disp = &display_controller;
    encoder = &input;
}

void OptionsMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);
    disp->createMenu(menuList);
    activeMenu = true;
}

void OptionsMenu::handleKnobEvent() {
    //!@todo KnobEvent, salvar o nome do menu sempre que a flecha apontar para ele
}

void OptionsMenu::handlePressEvent() {
    callMenu();
}

void OptionsMenu::callMenu() {
    
  
}