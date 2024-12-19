#include "sensorPT100.hpp"
/*
############################################################
####################      PT100     ########################
############################################################
*/
SensorPT100::SensorPT100(const std::string& id){
    sensor_id = id;
    sensorIDint = SENSOR_ID_PT100; // Define sensorIDint para associar o PT100 com o threshold correspondente na interface (ID do PT100 = 3)
    max_module.begin(MAX31865_3WIRE);
}

void SensorPT100::enableSensor() {
    is_enabled = true;
}

void SensorPT100::disableSensor() {
    is_enabled = false;
}

void SensorPT100::setCalibration(float gain, float offset) {
    this->gain = gain;
    this->offset = offset;
}


float SensorPT100::getTemperature() {
    float tempRTD;
    tempRTD = max_module.temperature(RNOMINAL, RREF);

    tempRTD = gain*tempRTD + offset;

    return tempRTD;
}

bool SensorPT100::isSensorEnabled() {
    return is_enabled;
}

std::string SensorPT100::getSensorID() {
    return sensor_id;
}

bool SensorPT100::checkSensorHealth() {
    return !(analogRead(SENSOR_PIN) <=  NOT_HEALTHY_THRESHOLD);
}

int8_t SensorPT100::getSensorIDint() {
    return sensorIDint;
}
