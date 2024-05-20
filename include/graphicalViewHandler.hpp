#ifndef _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
#define _INCLUDE_GRAPHICALVIEWHANDLER_HPP_

#include <optionsMenu.hpp>

class GraphicalViewHandler {
    public:
        void showOptionsMenu();
        void config(int upperBound, KnobEvent knob, ButtonPressEvent press);

        GraphicalViewHandler(OptionsMenu menu);

    private:
        OptionsMenu* mainMenu;
    };

#endif // _INCLUDE_GRAPHICALVIEWHANDLER_HPP_
