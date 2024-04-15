
#include "display.hpp"

Display disp;

int arrowPos = 0;

std::vector<std::string> menuList = {"Menu 1", "Menu 2", "Menu 3"};

void setup() {
  Serial.begin(9600);
  disp.displayConfig();
  //disp.displayTeste();

  //disp.displayText (135, 10);
  //disp.displayText (3.14f, 25);
  //disp.displayText("texto teste", 40);

  pinMode(UP_BUTTON_PIN, INPUT);
  pinMode(DOWN_BUTTON_PIN, INPUT);
  pinMode(SELECT_BUTTON_PIN, INPUT);
}

void loop() {

  disp.showMenuTitle();
  disp.createMenu(menuList);
  disp.upButton(); 
  disp.drawArrow(arrowPos);
  Serial.println(arrowPos);
  delay(500);                                       
  
}

