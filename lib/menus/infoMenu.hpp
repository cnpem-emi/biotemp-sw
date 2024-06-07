#ifndef _INFOMENU_HPP_
#define _INFOMENU_HPP_

#include "menuBase.hpp"
#include "displayController.hpp"

class InfoMenu : public MenuBase{
    public:
        int id;
        String menuName = "InfoMenu";

        InfoMenu(DisplayController display_controller);

        void showMenu() override;
        void updateMenu(int arrowPosition);
        void handleKnobEvent(KnobEvent event) override;
        void handlePressEvent(ButtonPressEvent event) override;

        std::string macAdress;
        bool espRegisteredStatus = false;


    private:
        int arrowPosition = 0;
        DisplayController* disp;

        std::vector<std::string> itemsList = {"A0:B7:65:DD:89:3C", "Device 1", "CNPEM"};

};

#endif  // _INFOMENU_HPP_