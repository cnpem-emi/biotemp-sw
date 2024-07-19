#include "temphandler.hpp"
#include "sensorPT100.hpp"
#include "sensorNTC.hpp"

using TempSensorPtr = std::shared_ptr<TemperatureSensorBase>;


void TempHandler::addPT100Sensor(const std::string& sensor_id) {
    available_sensors[sensor_id] = TempSensorPtr(new SensorPT100(sensor_id));
    isAnySensorConfig = true;
}

void TempHandler::addNTCSensor(const std::string& sensor_id, const int sensor_pin){
    available_sensors[sensor_id] =  TempSensorPtr(new SensorNTC(sensor_pin));
    isAnySensorConfig = true;
}

float TempHandler::getTemperature(const std::string& sensor_id){
    return available_sensors[sensor_id]->getTemperature();
}

void TempHandler::checkThreshold(){
    uint8_t triggered_count = 0;
    for ( auto it = available_sensors.begin(); it != available_sensors.end(); ++it) {
        if((it->second)->getTemperature() > threshold){
            isThresholdTrespassed = true;
            
            triggered_count++;

            buzzer.buzzerON();
            led.ledON();
        }
    }

    if(triggered_count == 0) {
        buzzer.buzzerOFF();
        isThresholdTrespassed = false;
    }
}
