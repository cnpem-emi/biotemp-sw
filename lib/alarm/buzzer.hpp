#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include "sensorNTC.hpp"
#include "LED.hpp"

#define BUZZER_COUNTER_MAX 10 // Equivale a aproximadamente 41 segundos
#define BUZZER_PIN 15
#define ON_BUZZER_DURATION 100
#define OFF_BUZZER_DURATION 500
#define BUZZER_PWM_CHANNEL 0
//#define BUZZER_FREQUENCY 2500 // Frequência de 2.5kHz é a freq de ressonância do buzzer, por isso o volume fica muito alto
#define BUZZER_FREQUENCY 1000 // Frequência utilizada para fazer debugs e não ficar surdo
#define BUZZER_PWM_RESOLUTION 8 // Resolução do PWM (8 bits)

class Buzzer
{
    public:
        /** 
         *  Sets up the buzzer PWM channel and attaches it to a specific pin.
         */
        void buzzerConfig();

        /** 
         * Controls the state of a buzzer based on specified durations and updates the
         * buzzer state and LED brightness accordingly.
         */
        void buzzerON();

        /** 
         *  Turns off a buzzer by setting the digital output pin to LOW and the PWM channel to 0.
         */
        void buzzerOFF();

        /** 
         * Sets an enable flag based on the input parameter
         * and turns off the buzzer if the input is false.
         * 
         * @param enable Disables or Enables toggling 
         */ 
        void toggle(bool enable);

        bool isEnabled = true;

        void handleDisable();
        bool isBuzzerTriggered = false;
    
    private:
        int buzzerState = HIGH;
        long rememberTime = 0;
        int buzzerCounter = 0;

};

#endif  // _BUZZER_HPP_