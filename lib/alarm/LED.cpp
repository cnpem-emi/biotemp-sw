#include "LED.hpp"

void LED::ledConfig() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, ledState);
}

void LED::ledON() {
    if( ledState == HIGH )
    {
        if( (millis() - rememberTime) >= onDuration) {   
            ledState = LOW;// change the state of LED
            rememberTime = millis();// remember Current millis() time
        }
    } 
    else 
    {   
        if( (millis() - rememberTime) >= offDuration) {     
            ledState = HIGH;// change the state of LED
            rememberTime = millis();// remember Current millis() time
        }
    }
    digitalWrite(ledPin, ledState);// turn the LED ON or OFF
}

void LED::ledOFF() {
    digitalWrite(ledPin, LOW);
}
