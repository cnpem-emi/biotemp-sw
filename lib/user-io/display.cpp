#include "display.hpp"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void Display::displayConfig() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
    }
    display.clearDisplay();

    delay(2000);
}

void Display::displayText(int value, int line, bool newline) {
    pixelLine = line * 15;
    char buffer[10];
    itoa(value, buffer, 10);
    display.setTextSize(1);
    display.setTextColor(WHITE);

     if (newline == true) {
      display.setCursor(10, pixelLine);
      display.println(buffer);
    } else {
      display.print(buffer);
    }
    
    display.display();
}

void Display::displayText (float value, int line, bool newline) {
    char buffer[10];

    pixelLine = line * 15;
    dtostrf(value, 3, 2, buffer);
    display.setTextSize(1);
    display.setTextColor(WHITE);

    if (newline == true) {
      display.setCursor(10, pixelLine);
      display.println(buffer);
    } else {
      display.print(buffer);
    }

    display.display();
}

void Display::displayText (std::string text, int line, bool newline ) {
    pixelLine = line * 15;
    display.setTextSize(1);
    display.setTextColor(WHITE);

    if (newline == true) {
      display.setCursor(10, pixelLine);
      display.println(text.c_str());
    } else {
      display.print(text.c_str());
    }

    display.display();
}

int Display::getCenterX() {
  int displayWidth = display.width(); 
  return displayWidth / 2; 
}

void Display::showMenuTitle(String menuTitle) {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor((getCenterX() - menuTitle.length()) / 2 , 0);
  display.println(menuTitle.c_str());
  display.drawLine(0, EspacoLinha1, display.width(), EspacoLinha1, WHITE);
  display.display();
}

void Display::drawArrow(int line) {
  int gfxChar = 0x10;
  line += 1;
  pixelLine = line * 15; 
  display.setCursor(2, pixelLine);
  display.write(gfxChar);
  display.display();
}

void Display::clearDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.display();
}

void Display::upButton() {
    if (digitalRead(UP_BUTTON_PIN) == HIGH) {
        arrowPos++;
      if (arrowPos > 2) {
          arrowPos = 0; 
      }
      display.clearDisplay();
    }
}

void Display::downButton() {
    if (digitalRead(DOWN_BUTTON_PIN) == HIGH) {
        arrowPos--;
      if (arrowPos < 0) {
          arrowPos = 2; 
      }
      display.clearDisplay();
    }
}

void Display::selectButton() {
    if (digitalRead(SELECT_BUTTON_PIN) == HIGH) {
    Serial.print("Selected");
    }

}

void Display::createMenu(std::vector<std::string> menuList) {
  for(int i=0; i < menuList.size(); i++) {
    displayText(menuList[i], i+1, true);
  }
}
