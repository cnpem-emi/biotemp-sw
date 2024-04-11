#include "temphandler.hpp"

/*
############################################################
####################      PT100     ########################
############################################################
*/

void SensorPT100::enablePT100() {
    max.begin(MAX31865_3WIRE);
    enabled = true;
}

void SensorPT100::disablePT100() {
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

float SensorNTC::getTemperature() {
    float v_adc; // Voltage measured from the ADC
    float r_ntc; // NTC resistance

    v_adc = adcReader(); 
    v_adc = v_adc/1000;
    r_ntc = R_0/((3.3/v_adc)-1); 
    temperature = (BETA_COEFF*T_0)/(std::log(r_ntc/R_0)*T_0 + BETA_COEFF); // Gets the temperature in Kelvin
    temperature = temperature - 273.15; // Converts to Celsius

    return temperature;
}

float SensorNTC::adcReader() {
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

SensorNTC::SensorNTC(int id) {
    ntcID = id;
    sensorID = "NTC " + std::to_string(ntcID);
}
