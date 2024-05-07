#include "sensorPT100.hpp"
/*
############################################################
####################      PT100     ########################
############################################################
*/
void SensorPT100::enableSensor() {
    max_module.begin(MAX31865_3WIRE);
    is_enabled = true;
}

void SensorPT100::disableSensor() {
    is_enabled = false;
}

float SensorPT100::getTemperature() {
    float tempRTD;
    tempRTD = max_module.temperature(100, RREF);

    return tempRTD;
}
