#include "../include/temphandler.hpp"

/*
############################################################
####################      PT100     ########################
############################################################
*/

#define CS_PIN 10
#define RREF 430.0

Adafruit_MAX31865 max = Adafruit_MAX31865(CS_PIN);

void SensorPT100::enablePT100() {
    digitalWrite(CS_PIN, HIGH);
    max.begin(MAX31865_3WIRE);
    enabled = true;
}

void SensorPT100::disablePT100() {
    digitalWrite(CS_PIN, LOW);
    enabled = false;
}

float SensorPT100::getTemperature() {
    float tempRTD;
    tempRTD = max.temperature(100, RREF);

    return tempRTD;
}

/*
############################################################
####################       NTC      ########################
############################################################
*/

#define ADC1_PIN 3
#define ADC2_PIN 2

void SensorNTC::enableNTC() {
    enabled = true;
}

void SensorNTC::disableNTC() {
    enabled = false;
}

void SensorNTC::lienarizeADC() {
    // Usar método de linearização
    
}

float SensorNTC::getTemperature() {
    // Ler ADC (Usar função específica)
    // retornar valor de temperatura
}

int SensorNTC::adcReader(int ntcID) {
    int adcValue;

    switch(ntcID) {
        case 1:
            adcValue = analogReadMilliVolts(ADC2_PIN);
            break;

        case 2:
            adcValue = analogReadMilliVolts(ADC2_PIN);
            break;

        default:
            adcValue = analogReadMilliVolts(ADC2_PIN);
            break;
    }
    
    return adcValue;
}
