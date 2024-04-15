#ifndef _INCLUDE_DISPLAY_HPP_
#define _INLCUDE_DISPLAY_HPP_

//INCLUDES
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define UP_BUTTON_PIN 4
#define DOWN_BUTTON_PIN 3
#define SELECT_BUTTON_PIN 2

class Display {
    public:
        void displayConfig();
        void displayTeste();

        void displayText(int value, int pixelLine, bool newline);
        void displayText(float value, int pixelLine, bool newline);
        void displayText(std::string text, int line, bool newline);
        
        int pixelLine = 0;
        int getCenterX();

        void showMenuTitle();
        void drawArrow(int line);
        void clearDisplay();
        void createMenu(std::vector<std::string> menuList);
        void upButton();
        void downButton();
        void selectButton();


        int arrowPos = 0;
        const byte EspacoLinha1 = 9;              // espaçamento entre linhas (6 linhas)
        

    private:
        
};

#endif // _INCLUDE_DISPLAY_HPP_