#ifndef _TEMPMENU_HPP_
#define _TEMPMENU_HPP_

#include <menuBase.hpp>

#define DEFAULT_THRESHOLD 3.0 // Default temperature threshold to set the alarm

// Operation modes
typedef enum {
    DEFAULT_MODE,
    ULTRAFREEZER_MODE,
    FREEZER_MODE,
    REFRIGERATOR_MODE,
    AMBIENT_MODE
} Modes;

/*********************************************************/
/*!
    @brief Temperature Menu interface class. Creates the menu
        that handles inputs and changes in the sensors parameters.
*/
/*********************************************************/
class TempMenu : public MenuBase {
    public:

        /******************************************************/
        /*!
            @brief shows the temperature menu on the device screen.
            @param display The display object where the menu will be shown.
        */
        /******************************************************/
        void showMenu(DisplayController display) override;

        /******************************************************/
        /*!
            @brief Handles the input controller events.
            @param event The callback event from the input controller.
        */
        /******************************************************/
        void handleInputEvent(ButtonEvent event) override;

    private:
        String menuName = "TempMenu"; // Menu title shown on screen. 
        std::vector<std::string> itemsList = {"Item1", "Item2", "Item3"}; // List of items to be shown on screen.
        float currentThreshold = DEFAULT_THRESHOLD; // Temperature tolerance to activate the alarm
        Modes currentMode = DEFAULT_MODE; // Device operation mode

        /*****************************************************/
        /*!
            @brief Sets the device operation mode.
            @param mode The mode to be set.
        */
        /*****************************************************/
        void setMode(Modes mode);

        /*****************************************************/
        /*!
            @brief Sets the threshold for the temperature measurement.
            @param new_threshold The new threshold to be set.
        */
        /*****************************************************/
        void setThreshold(float new_threshold);
};

#endif  // _TEMPMENU_HPP_