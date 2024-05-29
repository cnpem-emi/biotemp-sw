#include "optionsMenu.hpp"

OptionsMenu::OptionsMenu(
        DisplayController display_controller, 
        TempMenu temp
            ) {
    //activeMenu = true;

    disp = &display_controller;

    temp_menu = &temp;
    menuList.emplace_back(temp_menu); // id = 0
    menuNamesList.emplace_back(temp_menu->menuName.c_str());

    TempMenu* temp2; //REMOVER
    temp2 = &temp; //REMOVER
    menuList.emplace_back(temp2); //REMOVER
    menuNamesList.emplace_back(temp2->menuName.c_str()); //REMOVER
}

void OptionsMenu::showMenu() {
    disp->clearDisplay();
    disp->drawArrow(arrowPosition);
    disp->showMenuTitle(menuName);
    disp->createMenu(menuNamesList);
    activeMenu = true;
}

void OptionsMenu::updateMenu(int newArrowPosition){
    disp->eraseArrow();
    disp->drawArrow(newArrowPosition);
}

void OptionsMenu::handleKnobEvent(KnobEvent event) {
    arrowPosition = event.position;
    if (activeMenu == true) {
        if (event.isScreenSaverOn == true){
            showMenu();
        }
        else {
            updateMenu(event.position - 1);
        }
    } else {
        disp->clearDisplay();
        menuList[0]->handleKnobEvent(event);
    }
}

void OptionsMenu::handlePressEvent(ButtonPressEvent event) {
    if (event.isScreenSaverOn == true){
        activeMenu = true;
        showMenu();
    } else {
        activeMenu = false; 
        // @TODO change this to id of menu
        menuList[arrowPosition]->handlePressEvent(event);
    }
}
