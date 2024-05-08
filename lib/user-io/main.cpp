
#include "display.hpp"

Display disp;

std::vector<std::string> menuList = {"Menu 1", "Menu 2", "Menu 3"};



void setup() {
  Serial.begin(9600);
  disp.displayConfig();

  pinMode(UP_BUTTON_PIN, INPUT);
  pinMode(DOWN_BUTTON_PIN, INPUT);
  pinMode(SELECT_BUTTON_PIN, INPUT);
}

void loop() {
  disp.showMenuTitle("Menu Principal");
  disp.createMenu(menuList);
  disp.upButton();
  disp.downButton(); 
  disp.drawArrow(disp.arrowPos);
  Serial.println(disp.arrowPos);
  delay(100);                                       
  
}

