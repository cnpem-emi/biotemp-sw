#include "optionsMenu.hpp"

OptionsMenu::OptionsMenu (DisplayController display_controller):
 temp_menu(display_controller), info_menu(display_controller) {
    //isCurrentlyActiveMenu = true;

    activeMenu = this;

    disp = &display_controller;
    
    menuNamesList.emplace_back(temp_menu.menuName.c_str());
    menuNamesList.emplace_back(info_menu.menuName.c_str());

}

void OptionsMenu::showMenu() {
    disp->clearDisplay();
    disp->drawArrow(arrowPosition);
    disp->showMenuTitle(menuName);
    disp->createMenu(menuNamesList[0], menuNamesList[1]);
    changeCurrentlyActiveMenu(MAIN_MENU);
}

void OptionsMenu::updateMenu(int newArrowPosition){
        disp->eraseArrow();
        disp->drawArrow(newArrowPosition);
}

void OptionsMenu::handleKnobEvent(KnobEvent event) {
    arrowPosition = event.position;
    isScreenSaverOn = event.isScreenSaverOn;

    if (event.isScreenSaverOn == true){
            showMenu();
        }
    else {
         if (activeMenu == this){
            updateMenu(event.position - 1);
        }
        else {
            activeMenu->handleKnobEvent(event);
        }
    }
}

void OptionsMenu::changeCurrentlyActiveMenu(MENU_OPTIONS id) {
    switch (id)
    {
        case MAIN_MENU:
            activeMenu = this;    
            break;
        case TEMP_MENU:
            activeMenu = &temp_menu;
            break;
        case INFO_MENU:
            activeMenu = &info_menu;
            break;
        default:
            activeMenu = this;
            break;
    }
}

void OptionsMenu::handlePressEvent(ButtonPressEvent event) {
    if (isScreenSaverOn == true){
        isScreenSaverOn = false;
        changeCurrentlyActiveMenu(MAIN_MENU);
        showMenu();

        return; 
    }

    if(arrowPosition == RETURN_POS)
    {
        requestScreenSaver = true;
    }
    else if (activeMenu == this){
        changeCurrentlyActiveMenu(static_cast<MENU_OPTIONS>(arrowPosition));
        activeMenu->showMenu();
    }
    else {
        activeMenu->handlePressEvent(event);
    }
}
