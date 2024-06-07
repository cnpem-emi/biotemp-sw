#include "optionsMenu.hpp"

OptionsMenu::OptionsMenu (DisplayController display_controller):
 temp_menu(display_controller), info_menu(display_controller) {
    //activeMenu = true;

    disp = &display_controller;
    
    //temp_menu = &temp;
    //temp_menu->id = 0;
    //menuList.emplace_back(temp_menu); // id = 0
    menuNamesList.emplace_back(temp_menu.menuName.c_str());

    //info_menu = &info;
    //info_menu->id = 1;
    //menuList.emplace_back(info_menu); 
    menuNamesList.emplace_back(info_menu.menuName.c_str());

    //temp_menu = TempMenu temp_menu(display_controller);
    //info_menu = InfoMeny info_menu(display_controller);

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
        //menuList[0]->handleKnobEvent(event);
    }
}


void OptionsMenu::handlePressEvent(ButtonPressEvent event) {
    if (activeMenu == false){
        activeMenu = true;
        showMenu();
    } else {
        //activeMenu = false; 
        // @TODO change this to id of menu
        //menuList[arrowPosition]->handlePressEvent(event);
        Serial.println(arrowPosition);
        switch (arrowPosition)
        {
        case 1:
            temp_menu.handlePressEvent(event);
            break;
        case 2:
            info_menu.handlePressEvent(event);
            break;
        }

    }
}
