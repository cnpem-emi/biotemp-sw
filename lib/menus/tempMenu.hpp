#ifndef _TEMPMENU_HPP_
#define _TEMPMENU_HPP_

#include "menuBase.hpp"
#include "displayController.hpp"
#include "modes-and-layouts.hpp"
#include "temphandler.hpp"

#include<map>
#include<string>


/*********************************************************/
/*!
    @brief Temperature Menu interface class. Creates the menu
        that handles inputs and changes in the sensors parameters.
*/
/*********************************************************/
class TempMenu : public MenuBase {
    public:
        
        std::map<OperationModes, std::string> MODES_DISPLAY_STR = {{ULTRAFREEZER_MODE, "UltraFreezer"},
                                                                   {FREEZER_MODE, "Freezer"},
                                                                   {REFRIGERATOR_MODE, "Refrig."},
                                                                   {AMBIENT_MODE, "Ambient"}};

        std::map<SensorLayouts, std::string> SENSOR_LAYOUTS_STR = {{NONE, "None"},
                                                                   {NTC1, "NTC1"},
                                                                   {NTC2, "NTC2"},
                                                                   {PT100, "PT100"}}; // List of items to be shown on screen.

        int id = 0;
        String menuName = "TempMenu"; // Menu title shown on screen. 

        TempMenu(DisplayController display_controller, TempHandler* &tempHandler);

        /******************************************************/
        /*!
            @brief shows the temperature menu on the device screen.
            @param display The display object where the menu will be shown.
        */
        /******************************************************/
        //void showMenu() override;
        void showMenu();

        void updateMenu(int arrowPosition);


    private:
        DisplayController* disp;

        
        OperationModes currentMode = AMBIENT_MODE; // Device operation mode
        SensorLayouts currentLayout = NONE;

        /*****************************************************/
        /*!
            @brief Sets the device operation mode.
            @param mode The mode to be set.
        */
        /*****************************************************/
        void setMode(OperationModes mode);
        void setSensorLayout(SensorLayouts sensorLayout);
        TempHandler* &tempHandler;

};

#endif  // _TEMPMENU_HPP_
