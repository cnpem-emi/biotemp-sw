#ifndef _MENUBASE_HPP_
#define _MENUBASE_HPP_

#include <vector>
#include <string>
//#include "displayController.hpp"
#include "InputEvent.hpp"

class MenuBase {
    public:
        int id; // ID of the menu class.
        std::string menuName; // Name of the menu class.
        
        // Shows the specified menu.
        virtual void showMenu() = 0;

        /**********************************************************/
        /*!
            @brief Handles the events called by the encoder knob.
            @param event The event struct instance.
        */
        /**********************************************************/
        virtual void handleKnobEvent(KnobEvent event) = 0;

        /**********************************************************/
        /*!
            @brief Handles the events called by the encoder button.
            @param event The event struct instance.
        */
        /**********************************************************/
        virtual void handlePressEvent(ButtonPressEvent event) = 0;

    protected:
        int arrowPosition; // Position of the arrow of the menu instance.

};

#endif  // _MENUBASE_HPP_
