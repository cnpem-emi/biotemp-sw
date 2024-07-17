#ifndef _LED_HPP_
#define _LED_HPP_

#include <Arduino.h>

#define ledPin 39

class LED
{
public:
    void ledConfig();
    void ledON();
};


#endif // _LED_HPP