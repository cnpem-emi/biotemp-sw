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


void TempMenu::setSensorLayout(SensorLayouts sensorLayout){
    currentLayout = sensorLayout;
    tempHandler->setSensorLayout(sensorLayout);
}

void TempMenu::setMode(OperationModes mode) {
    currentMode = mode;
    tempHandler->setOperationMode(mode);
}

