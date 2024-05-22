#include "optionsMenu.hpp"

OptionsMenu::OptionsMenu(
        DisplayController display_controller, 
        TempMenu temp
            ) {

    disp = &display_controller;

    temp_menu = &temp;
    menuList.emplace_back(temp_menu); // id = 0
    menuNamesList.emplace_back(temp_menu->menuName.c_str());
}

void OptionsMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);
    disp->createMenu(menuNamesList);
    activeMenu = true;
}

void OptionsMenu::handleKnobEvent(KnobEvent event) {
    if (activeMenu != true) {
        menuList[id]->handleKnobEvent(event);
    }
    
}

void OptionsMenu::handlePressEvent(ButtonPressEvent event) {
    if (activeMenu != -1){
        menuList[id]->handlePressEvent(event);
    } else {

    }
}
