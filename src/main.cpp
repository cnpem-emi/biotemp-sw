#include <Arduino.h>
#include <InputController.hpp>

#include "temphandler.hpp"
#include "display.hpp"

Display disp;
std::vector<std::string> menuList = {"Menu 1", "Menu 2", "Menu 3"};

InputController encoder;

void setup() {
  encoder.config(2);
  TempHandler temp_handler; 
  Serial.begin(9600);
  disp.displayConfig();
  
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