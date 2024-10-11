#include "temphandler.hpp"
#include "sensorPT100.hpp"
#include "sensorNTC.hpp"
#include "biotempDataJSON.hpp"

void TempHandler::addPT100Sensor(const std::string& sensor_id) {
    available_sensors[sensor_id] = TempSensorPtr(new SensorPT100(sensor_id));
    available_sensors[sensor_id]->enableSensor();
    isAnySensorConfig = true;
}


void TempHandler::addNTCSensor(const std::string& sensor_id, const int sensor_pin){
    available_sensors[sensor_id] =  TempSensorPtr(new SensorNTC(sensor_pin));
    available_sensors[sensor_id]->enableSensor();
    isAnySensorConfig = true;
}

void TempHandler::clearSensorMap(){
    available_sensors.clear();
    isAnySensorConfig = false;
}



void TempHandler::setSensorLayout(SensorLayouts sensorLayout) {
    currentLayout = sensorLayout;
    clearSensorMap();
    
    // int sensor_1_type = configDoc["sensor_1_type"] | -1;
    // int sensor_2_type = configDoc["sensor_2_type"] | -1;
    // int sensor_3_type = configDoc["sensor_3_type"] | -1;


    // if (sensor_1_type == 1) {
    //     addNTCSensor(NTC_ID_1, NTC_PIN_1);
    // } else if (sensor_1_type == 2) {
    //     addNTCSensor(NTC_ID_2, NTC_PIN_2);
    // } else if (sensor_1_type == 3) {
    //     addPT100Sensor(PT100_ID);
    // }

    // if (sensor_2_type == 1) {
    //     addNTCSensor(NTC_ID_1, NTC_PIN_1);
    // } else if (sensor_2_type == 2) {
    //     addNTCSensor(NTC_ID_2, NTC_PIN_2);
    // } else if (sensor_2_type == 3) {
    //     addPT100Sensor(PT100_ID);
    // }

    // if (sensor_3_type == 1) {
    //     addNTCSensor(NTC_ID_1, NTC_PIN_1);
    // } else if (sensor_3_type == 2) {
    //     addNTCSensor(NTC_ID_2, NTC_PIN_2);
    // } else if (sensor_3_type == 3) {
    //     addPT100Sensor(PT100_ID);
    // }
    

    
    switch(currentLayout) {
        case NTC1:
            addNTCSensor(NTC_ID_1, NTC_PIN_1);
            break; 
        case NTC2:
            addNTCSensor(NTC_ID_1, NTC_PIN_1);
            addNTCSensor(NTC_ID_2, NTC_PIN_2);
            break;
        case PT100:
            addPT100Sensor(PT100_ID);
            break;
    }
}


float TempHandler::getTemperature(const std::string& sensor_id){
    return available_sensors[sensor_id]->getTemperature();
}

TempResults TempHandler::getAllTemperatures(){
    TempResults tempResults;
    for ( auto it = available_sensors.begin(); it != available_sensors.end(); ++it) {
        tempResults[it->first] = (it->second)->getTemperature();
    }
    return tempResults;
}


bool TempHandler::getSensorsHealth(){
    for ( auto it = available_sensors.begin(); it != available_sensors.end(); ++it) {
        if(!(it->second)->checkSensorHealth()){ return false;}
    }
    return true;
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
        led.ledOFF();
        isThresholdTrespassed = false;
    }
}
