#include "LED.hpp"

void LED::ledConfig() {
    pinMode(ledPin, OUTPUT);
}

void LED::ledON() {
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);
    delay(500);
}