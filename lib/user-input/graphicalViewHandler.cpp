#include "graphicalViewHandler.hpp"

/** 
 * Turns off the screen saver and displays the main menu.
 */
void GraphicalViewHandler::showOptionsMenu() {
    isScreenSaverOn = false;
    mainMenu.showMenu();
}

/** 
 * Updates the screen saver flag and then passes the event to the `mainMenu` object.
 * 
 * @param event The `event` parameter is an object of type `KnobEvent`, 
 *  contains information about the positivion update of the knob. 
 */
void GraphicalViewHandler::handleKnobEvent(KnobEvent event) {
    event.isScreenSaverOn = isScreenSaverOn;

    if (isScreenSaverOn == true) {
        isScreenSaverOn = false;
    }
    mainMenu.handleKnobEvent(event);
}

/** 
 * Updates the screen saver status, handles the button press event in the main menu,
 * and resets the pressed state of the event.
 * 
 * @param event The `event` parameter is of type `ButtonPressEvent`, which contains information
 * about a button press event, such as the button that was pressed and any other underlying related information.
 */
void GraphicalViewHandler::handlePressEvent(ButtonPressEvent event) {
    event.isScreenSaverOn = isScreenSaverOn;
    if (isScreenSaverOn == true) {
        isScreenSaverOn = false;
    }
    mainMenu.handlePressEvent(event);
    event.pressed = false;
}

/** 
 * Displays configuration on an OLED screen and adds a temperature handler and MQTT client to itself.
 * 
 * @param tempHandler The `tempHandler` parameter is an object of the `TempHandler` class, which is
 * used to handle temperature-related operations or data.
 * @param mqttClient The `mqttClient` parameter is an instance of the `BioTempMQTTClient` class, which
 * is used for handling MQTT communication related to temperature data in the context of the Biotemp Product.
 */
void GraphicalViewHandler::config(TempHandler& tempHandler, BioTempMQTTClient& mqttClient) {
    oled.displayConfig();
    addTempHandler(tempHandler);
    addMQTTClient(mqttClient);
}

/** 
 *  Displays a logo on the screen for a specified number of seconds 
 *  before clearing the display.
 * 
 * @param Logo The `Logo` parameter is an array of unsigned characters representing the image data of a
 * logo to be displayed on the OLED screen.
 */
void GraphicalViewHandler::splashScreen(const unsigned char Logo[]){
    oled.showLogo(Logo);
    delay(SPLASH_SCREEN_TIME);
    oled.clearDisplay();
}

/** 
 * Clears the display and updates the screen saver.
 */
void GraphicalViewHandler::showScreenSaver(){
    oled.clearDisplay();
    updateScreenSaver(); 
}

/** 
 * Clears the display, shows the menu title, and displays a message if temperature sensors are not available.
 * 
 * @return early if there are no available sensors. It displays a message on the OLED screen saying
 * "Please Configure Temperature Sensor" and then returns without executing any further code in the
 * function.
 */
void GraphicalViewHandler::updateScreenSaver() {
    oled.clearDisplay();
    oled.showMenuTitle("BioTemp");

    if(tempHandler->available_sensors.empty()) {
        oled.displayText("Please Configure", 1, true);
        oled.displayText("  Temperature Sensor", 2, false);
        return;
    }

    for ( auto it = tempHandler->available_sensors.begin();
          it != tempHandler->available_sensors.end(); ++it) {

        oled.displayText((it->first), 1, false);
        oled.displayText(": ", 1, false);
        oled.displayText((it->second)->getTemperature(), 1, false);
        oled.displayText("oC", 1, true); 
    }

    if(!tempHandler->isThresholdTrespassed){
        oled.displayText("Temperature OK", 3, false);     
    }
    else {
        oled.displayText("Sensors Triggered", 3, false);     
    }
}

/** 
 * The mainLoop function in the GraphicalViewHandler class checks if a screen saver needs to be shown
 * and performs related actions as the main core of the Biotemp Product. 
 */
void GraphicalViewHandler::mainLoop(){
    // Checks if Screen saver needs to be shown
    if (screenSaverEventScheduled == true || mainMenu.requestScreenSaver == true) 
    { 
    
      if(mqttClient != nullptr)
        mqttClient->publishTemp();

      mainMenu.requestScreenSaver = false;
      if (isScreenSaverOn == true) {
        updateScreenSaver();
        screenSaverEventScheduled = false;
      }
      else {
       showScreenSaver();
       isScreenSaverOn = true;
      }
    }

    if(tempHandler != nullptr)
        tempHandler->checkThreshold();

}


