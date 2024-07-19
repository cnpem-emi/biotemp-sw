#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include "sensorNTC.hpp"
#include "LED.hpp"

#define BUZZER_PIN 15
#define ON_BUZZER_DURATION 100
#define OFF_BUZZER_DURATION 500
#define BUZZER_PWM_CHANNEL 0
#define BUZZER_FREQUENCY 2000 // Frequência em Hz (2000 Hz = 2 kHz)
#define BUZZER_PWM_RESOLUTION 8 // Resolução do PWM (8 bits)

class Buzzer
{
    public:
        void buzzerConfig();
        void buzzerON();
        void buzzerOFF();
        void toggle(bool enable);
        bool isEnabled = true;
    
    private:
        int buzzerState = HIGH;
        long rememberTime = 0;

};

#endif  // _BUZZER_HPP_