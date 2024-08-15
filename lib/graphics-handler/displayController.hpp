#ifndef _INCLUDE_DISPLAYCONTROLLER_HPP_
#define _INCLUDE_DISPLAYCONTROLLER_HPP_

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <vector>

#include "debug-config.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)

#define UP_BUTTON_PIN 4 // Push button test up pin
#define DOWN_BUTTON_PIN 19 // Push button test down pin
#define SELECT_BUTTON_PIN 3 // Push button test select pin

#define I2C_DEFAULT_ADDR 0x3C
#define STARTUP_CONFIG_DELAY 2000 

#define TEXT_BUFFER_LEN 10 
#define NORMAL_TEXT_SIZE 1
#define TITLE_TEXT_SIZE 2
/***************************************************************/
/** 
    @brief SSD1306 display interface class. This module is a
    higher-level abstraction to the Adafruit_SSD1306.h library
    made to easily create interactive menus.
*/
/***************************************************************/
class DisplayController {
    public:
        int arrowPos = 0; // Position  of the menu arrow

        /**
         * Initializes an SSD1306 display and clears its contents.
         * Display initial configuration. Needs to be called inside the setup function.
         */
        void displayConfig();
        
        /***************************************************************/
        /*!
            @brief Displays the text input from the user.
            @param value Integer value to be printed.
            @param line The line in the display to be printed.
            @param newLine End the line if true.
        */
        /***************************************************************/
        void displayText(int value, int line, bool newline);
        /***************************************************************/
        /*!
            @brief Displays the text input from the user.
            @param value Float value to be printed.
            @param line The line in the display to be printed.
            @param newLine End the line if true.
        */
        /***************************************************************/
        void displayText(float value, int line, bool newline);
        /***************************************************************/
        /*!
            @brief Displays the text input from the user.
            @param text Text to be printed.
            @param line The line in the display to be printed.
            @param newLine End the line if true.
        */
        /***************************************************************/
        void displayText(std::string text, int line, bool newline);
        
        // Clears the display.
        void clearDisplay();
        
        /***************************************************************/
        /*!
            @brief Shows the menu title.
            @param menuTitle The menu title string.
        */
        /***************************************************************/
        void showMenuTitle(String menuTitle);

        /***************************************************************/
        /*!
            @brief Draws an arrow in the screen.
            @param line The line on which the arrow is drawn.
        */
        /***************************************************************/
        void drawArrow(int line);

        /***************************************************************/
        /*!
            @brief Creates a menu.
            @param menuList A vector with the strings of the menus.
        */
        /***************************************************************/
        void createMenu(std::string item1, std::string item2);

        // Erases the arrows drawn ion screen
        void eraseArrow();

        // Erases the temperature value
        void eraseTemperature();

        void showLogo(const unsigned char logo[]);

    private:
        int pixelLine = 0; // Number of pixels between lines
        const byte EspacoLinha1 = 10; // Spacing between lines (showMenuTitle)

        // Gets the center position of the display
        int getCenterX();

        /***************************************************************/
        /*!
            @brief Blueprint function for erasing parts of the text writen 
                on screen. It draws a rectangle with the specified parameters.
            @param x the initial x coordenate.
            @param y the initial y coordenate.
            @param size_x the final x coordenate.
            @param size_y the final y coordenate.
        */
        /***************************************************************/
        void eraseText(int x, int y, int size_x, int size_y);   
};

#endif  // _INCLUDE_DISPLAYCONTROLLER_HPP_
