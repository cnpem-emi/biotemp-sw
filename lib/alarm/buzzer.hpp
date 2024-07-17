#ifndef _BUZZER_HPP_
#define _BUZZER_HPP_

#include "sensorNTC.hpp"
#include "LED.hpp"

#define buzzerPin 15
#define pwmChannel 0
#define frequency 2000
#define resolution 8

class Buzzer
{
    public:
        void alarm();
        void buzzerConfig();
        void buzzerON();
    
    private:
        SensorNTC sensor1 = SensorNTC(1);
        LED led;
         

};



#endif  // _BUZZER_HPP_