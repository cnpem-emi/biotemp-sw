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
    disp->drawArrow(arrowPosition);
    disp->showMenuTitle(menuName);
    disp->createMenu(menuNamesList);
    activeMenu = true;
}

void OptionsMenu::handleKnobEvent(KnobEvent event) {
    if (activeMenu == true) {
        arrowPosition = event.position - 1;
        disp->eraseArrow();
        disp->drawArrow(arrowPosition);
    } else {
        disp->clearDisplay();
        menuList[id]->handleKnobEvent(event);
    }
}

void OptionsMenu::handlePressEvent(ButtonPressEvent event) {
    if (activeMenu == true){
        showMenu();
    } else {
        menuList[id]->handlePressEvent(event);
        //menuList[id]->showMenu();
        //activeMenu = false;
    }
}
