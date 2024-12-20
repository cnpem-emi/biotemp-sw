#include "sensorNTC.hpp"
/*
############################################################
####################       NTC      ########################
############################################################
*/

SensorNTC::SensorNTC(int ntc_id) {
    sensor_id = "NTC" + std::to_string(ntc_id);
    
    sensorIDint = ntc_id;

    sensor_pin = ADC1_PIN; // Defaults to ADC1

    if (sensor_id == NTCID2){
        sensor_pin = ADC2_PIN;
    }
}

void SensorNTC::enableSensor() {
    is_enabled = true;
}

void SensorNTC::disableSensor() {
    is_enabled = false;
}

void SensorNTC::setCalibration(float gain, float offset) {
    this->gain = gain;
    this->offset = offset;
}

float SensorNTC::getTemperature() {
    float voltage_adc; // Voltage measured from the ADC
    float resistence_ntc; // NTC resistance
    float temperature;

    voltage_adc = readADCPin(); 
    voltage_adc = voltage_adc/1000;
    resistence_ntc = R_DIV/((3.3/voltage_adc)-1);
    
    // Gets the temperature in Kelvin
    temperature = (BETA_COEFF*T_0)/(std::log(resistence_ntc/R_0)*T_0 + BETA_COEFF); 
    temperature = temperature - 273.15; // Converts to Celsius

    temperature = gain*temperature + offset;

    return temperature;
}

float SensorNTC::readADCPin() {
    float adc_value;

    adc_value = analogReadMilliVolts(sensor_pin);

    return adc_value;
}

bool SensorNTC::isSensorEnabled() {
    return is_enabled;
}

std::string SensorNTC::getSensorID() {
    return sensor_id;
}

bool SensorNTC::checkSensorHealth() {
    return !(analogRead(sensor_pin) <=  NOT_HEALTHY_THRESHOLD);
}

int8_t SensorNTC::getSensorIDint() {
    return sensorIDint;
}