#include "displayController.hpp"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void DisplayController::displayConfig() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, I2C_DEFAULT_ADDR)) { 
      DEBUG(Serial.println(F("SSD1306 allocation failed"));)
      while(true); // Infinite loop if this error occurs
                  //  (maybe handle it more graciously in the future?)
    }
    display.clearDisplay();

    delay(STARTUP_CONFIG_DELAY);
}

void DisplayController::displayText(int value, int line, bool newline) {
    char buffer[TEXT_BUFFER_LEN];
    itoa(value, buffer, TEXT_BUFFER_LEN);
    displayText(buffer, line, newline);
}

void DisplayController::displayText (float value, int line, bool newline,
                                     const uint8_t textSize, const uint16_t spacex) {
    char buffer[TEXT_BUFFER_LEN];
    dtostrf(value, 3, 2, buffer);   
    displayText(buffer, line, newline, textSize, spacex);
}

void DisplayController::displayText(std::string text, int line, bool newline, 
                                     const uint8_t textSize, const uint16_t spacex) {
    pixelLine = line * 16;
    display.setTextSize(textSize);

    display.setTextColor(WHITE);

    if (newline == true) {
      display.setCursor(spacex, pixelLine);
      display.println(text.c_str());
    } else {
      display.print(text.c_str());
    }

    display.display();
}

int DisplayController::getCenterX() {
  int displayWidth = display.width(); 
  return displayWidth / 2; 
}

void DisplayController::showMenuTitle(String menuTitle) {
  display.setTextSize(TITLE_TEXT_SIZE);
  display.setTextColor(WHITE);
  display.setCursor((getCenterX() - menuTitle.length()) / 2 , 0);
  display.println(menuTitle.c_str());
  display.display();
}

void DisplayController::drawArrow(int line) {
  display.setTextSize(NORMAL_TEXT_SIZE);
  int gfxChar = 0x10;
  line += 1;
  pixelLine = line * 16; 
  display.setCursor(2, pixelLine);
  display.write(gfxChar);
  display.display();
}

void DisplayController::eraseArrow() {
  eraseText(0, 16, 12, 48);
}

void DisplayController::eraseText(int x, int y, int size_x, int size_y) {
  display.drawRect(x, y, size_x, size_y, BLACK);
  display.fillRect(x, y, size_x, size_y, BLACK);
  display.display();
}

void DisplayController::clearDisplay() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.display();
}

void DisplayController::createMenu(std::string item1, std::string item2) {
    displayText(item1, 1, true);
    displayText(item2, 2, true);
    displayText("Return ", 3, true);
}

void DisplayController::showLogo(const unsigned char logo[]){
    display.clearDisplay();
    display.drawBitmap(0, 0, logo, 128, 64, WHITE);
    display.display();
}
