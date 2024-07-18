#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include "sensorNTC.hpp"
#include "LED.hpp"
#include "temphandler.hpp"

#define buzzerPin 15
#define onBuzzerDuration 100
#define offBuzzerDuration 500
#define pwmChannel 0
#define frequency 2000 // Frequência em Hz (2000 Hz = 2 kHz)
#define resolution 8 // Resolução do PWM (8 bits)

class Buzzer
{
    public:
        Buzzer(TempHandler& temp_handler) : temperature_handler{temp_handler} {}

        void alarm();
        void buzzerConfig();
        void buzzerON();
    
    private:
        TempHandler temperature_handler;
        LED led;
        int buzzerState = HIGH;
        long rememberTime = 0;
        

};



#endif  // _BUZZER_HPP_