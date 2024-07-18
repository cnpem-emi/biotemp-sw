#ifndef _LED_HPP_
#define _LED_HPP_

#include <Arduino.h>

#define ledPin 39
#define onDuration 500
#define offDuration 500


class LED
{
public:
    void ledConfig();
    void ledON();
private:
    int ledState = HIGH;
    long rememberTime = 0;
};


#endif // _LED_HPP