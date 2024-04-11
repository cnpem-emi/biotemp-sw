#ifndef _INCLUDE_DISPLAY_HPP_
#define _INLCUDE_DISPLAY_HPP_

//INCLUDES
#include <string>
#include <vector>


class GraphicalViewHandler {
    public:
        float pt100_temp;
        float ntc_1_temp;
        float ntc_2_temp;
        std::vector <int> menu_list;
        std::vector <int> menu_name_list;
        
        void button_pressed_event();
        void splash_screen();
        void status_screen();
        void defaut_screen();

        void option_menu(OptionsMenu);  
};

class OptionsMenu {
    public:
        std::string active_menu;

        void call_menu();
};

class Menu {
    public:
        int8_t arrow_position;
        std::string menu_name;

        void button_pressed_event();
        void show_menu();

    private:
            


};














#endif // _INCLUDE_DISPLAY_HPP_

