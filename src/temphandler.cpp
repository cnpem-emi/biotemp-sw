#include "../include/temphandler.hpp"

/*
############################################################
####################      PT100     ########################
############################################################
*/

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

void SensorNTC::enableNTC() {
    enabled = true;
}

void SensorNTC::disableNTC() {
    enabled = false;
}

float SensorNTC::getTemperature(int ntcID) {
    float v_adc;
    float r_ntc;
    float temperature;

    v_adc = adcReader(ntcID); // Voltage measured from the ADC
    r_ntc = R_0/((3.3/v_adc)-1); // NTC resistance
    temperature = (BETA_COEFF*T_0)/(std::log(r_ntc/R_0)*T_0 + BETA_COEFF); // Gets the temperature in Kelvin
    temperature = temperature - 273.15; // Converts to Celsius

    return temperature;
}

float SensorNTC::adcReader(int ntcID) {
    float adcValue;

    switch(ntcID) {
        case 1:
            adcValue = analogReadMilliVolts(ADC1_PIN);
            break;

        case 2:
            adcValue = analogReadMilliVolts(ADC2_PIN);
            break;

        default:
            adcValue = analogReadMilliVolts(ADC1_PIN);
            break;
    }
    
    return adcValue;
}
