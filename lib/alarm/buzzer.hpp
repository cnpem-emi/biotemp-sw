#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include "sensorNTC.hpp"
#include "LED.hpp"
#include "temphandler.hpp"

#define buzzerPin 15
#define pwmChannel 0
#define frequency 2000
#define resolution 8

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

};



#endif  // _BUZZER_HPP_