#include "tempMenu.hpp"

TempMenu::TempMenu(DisplayController display_controller, TempHandler* &temperatureHandler) 
    : tempHandler{temperatureHandler}{
    disp = &display_controller;
}

void TempMenu::showMenu() {
    disp->clearDisplay();
    disp->showMenuTitle(menuName);

    std::string modeDisplay = "Mode: ";
    modeDisplay = modeDisplay + MODES_DISPLAY_STR[currentMode];

    std::string sensorLayoutDisplay = "Layout: ";
    sensorLayoutDisplay = sensorLayoutDisplay + SENSOR_LAYOUTS_STR[currentLayout];

    disp->createMenu(modeDisplay, sensorLayoutDisplay);

    // Draw arrow at the beginning
    disp->eraseArrow();
    disp->drawArrow(FIRST_ITEM_POS-1);
}

void TempMenu::updateMenu(int arrowPosition){
    disp->eraseArrow();
    disp->drawArrow(arrowPosition);
}

void TempMenu::handleKnobEvent(KnobEvent event) {
     if (event.isScreenSaverOn == true){
            showMenu();
        }
        else {
            updateMenu(event.position - 1);
        }
}

void TempMenu::handlePressEvent(ButtonPressEvent event) {

    switch (event.position)
    {
        case  RETURN_POS:
            returnMenu->showMenu();
            break;
        case FIRST_ITEM_POS:
            setMode((OperationModes) (((int) currentMode+1) % MODES_NUM));
            showMenu();
            break;
        case SECOND_ITEM_POS:
            setSensorLayout((SensorLayouts) (((int) currentLayout + 1) % SENSOR_LAYOUTS_NUM));
            showMenu();
            disp->eraseArrow();
            disp->drawArrow(SECOND_ITEM_POS-1);
            break;
    }
}

void TempMenu::setSensorLayout(SensorLayouts sensorLayout){
    currentLayout = sensorLayout;
    tempHandler->setSensorLayout(sensorLayout);
}

void TempMenu::setMode(OperationModes mode) {
    currentMode = mode;
    tempHandler->setOperationMode(mode);
}

