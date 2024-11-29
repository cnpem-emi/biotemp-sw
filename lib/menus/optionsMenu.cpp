#include "optionsMenu.hpp"

OptionsMenu::OptionsMenu(DisplayController display_controller, TempMenu& tempMenu,
                          InfoMenu& infoMenu):
 temp_menu{tempMenu}, info_menu{infoMenu} {
    //isCurrentlyActiveMenu = true;

    activeMenu = this;
    returnMenu = this;

    disp = &display_controller;
    
    menuNamesList.emplace_back(temp_menu.menuName.c_str());
    menuNamesList.emplace_back(info_menu.menuName.c_str());

}

// void OptionsMenu::showMenu() {
//     disp->clearDisplay();
//     disp->drawArrow(arrowPosition);
//     disp->showMenuTitle(menuName);
//     disp->createMenu(menuNamesList[0], menuNamesList[1]);
//     // Draw arrow at the beginning
//     disp->eraseArrow();
//     disp->drawArrow(FIRST_ITEM_POS-1);
//     arrowPosition = FIRST_ITEM_POS;

//     changeCurrentlyActiveMenu(MAIN_MENU);
// }

// void OptionsMenu::updateMenu(int newArrowPosition){
//         disp->eraseArrow();
//         disp->drawArrow(newArrowPosition);
        
// }


// void OptionsMenu::changeCurrentlyActiveMenu(MENU_OPTIONS id) {
//     switch (id)
//     {
//         case MAIN_MENU:
//             activeMenu = this;    
//             break;
//         case TEMP_MENU:
//             activeMenu = &temp_menu;
//             break;
//         case INFO_MENU:
//             activeMenu = &info_menu;
//             break;
//         default:
//             activeMenu = this;
//             break;
//     }

//     activeMenu->returnMenu = this;
// }




